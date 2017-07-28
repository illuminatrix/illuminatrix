#include <kernel/cpu_setup.h>
#include <kernel/irq.h>
#include <kernel/io.h>
#include <stdio.h>
#include <stdint.h>
#include "interrupt.h"
#include "descriptor.h"

#define _IVT_LENGTH 51
#define _GDT_LENGHT 7

typedef void (*trapfn_t)(void);

static const trapfn_t intr_table[] = {
    intr_0, intr_1, intr_2,  intr_3,  intr_4,  intr_5,  intr_6,  intr_7,
    intr_8, intr_9, intr_10, intr_11, intr_12, intr_13, intr_14, intr_15
};

static const trapfn_t trap_table[] = {
    trap_0, trap_1, trap_2,  trap_3,  trap_4,  trap_5,  trap_6,  trap_7,
    trap_8, trap_9, trap_10, trap_11, trap_12, trap_13, trap_14, trap_15,
    trap_16, trap_17, trap_18
};

static idt_desc_t descriptor_table[_IVT_LENGTH];
static seg_desc_t segment_table[_GDT_LENGHT];
static tss_t tss;

static inline void
set_interrupt_descriptor(int32_t intno, trapfn_t f, int32_t sel, uint8_t type)
{
    descriptor_table[intno].offset_1 = (uint32_t)f;
    descriptor_table[intno].selector = sel;
    descriptor_table[intno].zero = 0;
    descriptor_table[intno].type_attr = type | ST_PRESENT;
    descriptor_table[intno].offset_2 = (((uint32_t)f) >> 16)&0xFFFF;
}

static inline void
fill_idt()
{
    int i;
    // cpu interrupts
    //for (i=0; i < sizeof(trap_table); i++) {
    //    set_interrupt_descriptor(i, trap_table[i], _TRAP_GATE_TYPE);
    //}
    //
    for (i=IRQ_OFFSET; i < _INTERRUPT_LENGTH + IRQ_OFFSET; i++) {
        set_interrupt_descriptor(i, intr_table[i], KERNEL_CS, ST_KERN | _INTERRUPT_GATE_TYPE);
    }
}

void
load_idt()
{
    fill_idt();
    struct
    {
        uint16_t length;
        uint32_t base;
    } __attribute__((packed)) IDTR;

    IDTR.length = _IVT_LENGTH * sizeof(idt_desc_t) - 1;
    IDTR.base = (uint32_t) descriptor_table;
    asm volatile ( "lidt %0" : : "m"(IDTR) );

    // This section should be rewrited without magic numbers
    // ========================================================
    // reset PIC
    _outb(PIC_MASTER_CTRL, 0x11);
    _outb(PIC_SLAVE_CTRL, 0x11);

    // change master interrupt to provided offset
    _outb(PIC_MASTER_DATA, IRQ_OFFSET);
    _outb(PIC_SLAVE_DATA, IRQ_OFFSET + 0x08);
    
    // setup cascade
    _outb(PIC_MASTER_DATA, 0x04);
    _outb(PIC_SLAVE_DATA, 0x02);
    
    // done
    _outb(PIC_MASTER_DATA, 0x01);
    _outb(PIC_SLAVE_DATA, 0x01);
    // ========================================================

    // Enable interrupts for PS2 and Serial bus
    _outb(PIC_MASTER_DATA, IRQ_MASK(IRQ1));
    _outb(PIC_SLAVE_DATA, IRQ_MASK(NO_IRQ));

    enable_idt();
}

static inline void
set_segment(int32_t vec, void *base, size_t limit, int32_t type, int32_t size)
{
    if (limit > 0xfffff) {
        limit >>= 12;
        size |= SIZE_4K;
    }
    segment_table[vec].limit_lo = limit;
    segment_table[vec].base_lo = (int32_t)base;
    segment_table[vec].type = type | ST_PRESENT;
    segment_table[vec].limit_hi = limit >> 16;
    segment_table[vec].size = size;
    segment_table[vec].base_hi = (int32_t)base >> 24;
}

void
load_gdt(void)
{
    /* Set system vector */
    set_segment(KERNEL_CS / 8, 0, 0xffffffff, ST_KERN | ST_CODE_R, SIZE_32);
    set_segment(KERNEL_DS / 8, 0, 0xffffffff, ST_KERN | ST_DATA_W, SIZE_32);
    set_segment(USER_CS / 8, 0, 0xffffffff, ST_USER | ST_CODE_R, SIZE_32);
    set_segment(USER_DS / 8, 0, 0xffffffff, ST_USER | ST_DATA_W, SIZE_32);

    /* Clear TSS Busy */
    segment_table[KERNEL_TSS / 8].type &= ~ST_TSS_BUSY;

    /* Load GDT */
    struct
    {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed)) GDTR;

    GDTR.limit = sizeof(segment_table) - 1;
    GDTR.base = (uint32_t)segment_table;
    asm volatile ( "lgdt %0" : : "m"(GDTR) );

    /* Reset code, data and stack selectors */
    asm volatile (
            "movzx %%ax, %%eax\n\t"
            "pushl %%eax\n\t"
            "pushl $1f\n\t"
            "lret\n\t"
            "1:\n\t"
            :
            :"a"(KERNEL_CS));
    asm volatile (
            "movw %0, %%ds\n\t"
            "movw %0, %%es\n\t"
            "movw %0, %%fs\n\t"
            "movw %0, %%gs\n\t"
            "movw %0, %%ss\n\t"
            :
            :"r"(KERNEL_DS));
}

static void
tss_init(void)
{
    set_segment(KERNEL_TSS / 8, &tss, sizeof(tss_t) - 1,
                ST_KERN | ST_TSS, 0);
    /* Setup TSS */
    memset(&tss, 0, sizeof(struct tss));
    tss.ss0 = KERNEL_DS;
    tss.esp0 = (uint32_t)(BOOT_STACK + PAGE_SIZE - 1);
    tss.cs = USER_CS | NON_PRIVILEGED;
    tss.ds = tss.es = tss.ss = tss.fs = tss.gs = USER_CS | NON_PRIVILEGED;
    tss.io_bitmap_offset = INVALID_IO_BITMAP;
    asm volatile (
        "ltr %%ax"
        :
        : "a"(KERNEL_TSS));
}

void
cpu_init(void)
{
    load_gdt();
    load_idt();
    tss_init();
}
