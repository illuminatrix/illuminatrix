#include <kernel/cpu_setup.h>
#include <kernel/irq.h>
#include <kernel/io.h>
#include <stdio.h>
#include <stdint.h>
#include "interrupt.h"

#define _IVT_LENGTH 51

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

static inline void
set_interrupt_descriptor(int intno, trapfn_t f, uint8_t type)
{
    descriptor_table[intno].offset_1 = (uint32_t)f;
    descriptor_table[intno].selector = 8;
    descriptor_table[intno].zero = 0;
    descriptor_table[intno].type = type;
    descriptor_table[intno].present = 1;
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
        set_interrupt_descriptor(i, intr_table[i], _INTERRUPT_GATE_TYPE);
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

void
cpu_init(void)
{
    load_idt();
}
