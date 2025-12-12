#include <stdint.h>
#include "idt.h"
#include "interrupt.h"

#define VECTORS 255

#define load_idtr(idt_ptr) \
    __asm__ volatile("lidtl %0 \n\t" \
                     :: "m" (idt_ptr))

struct idt_desc idt[VECTORS];
struct idt_register idtr;

void enable_interrupts(void)
{
    __asm__ volatile("sti \n\t");
}

void disable_interrupts(void)
{
    __asm__ volatile("cli \n\t");
}

void load_idt(void)
{
    extern void syscall_handler(void);
    extern void isr_0(void);
    extern void isr_1(void);
    extern void isr_10(void);
    extern void isr_11(void);

    uint32_t base = (uint32_t)isr_0;
    const uint32_t size_no_error = ((uint32_t)isr_1) - ((uint32_t)isr_0);
    const uint32_t size_w_error = ((uint32_t)isr_11) - ((uint32_t)isr_10);
    uint32_t offset = base;
    int i;

    for(i = 0; i <= 32 ; i++) {
        if ((i != 8 && i < 10) || (i > 14 && i != 17)) {
            idt[i].type = 0xE; //32 bit interrupt gate
            idt[i].p = 1;
            idt[i].s = 0;
            idt[i].seg_sel = 0x8; //Segment selector
            idt[i].offset15_0 = (uint16_t)(offset);
            idt[i].offset31_16 = (uint16_t)(offset >> 16);
            offset += size_no_error;
        } else {
            idt[i].type = 0xE; //32 bit interrupt gate
            idt[i].p = 1;
            idt[i].s = 0;
            idt[i].seg_sel = 0x8; //Segment selector
            idt[i].offset15_0 = (uint16_t)(offset);
            idt[i].offset31_16 = (uint16_t)(offset >> 16);
            offset += size_w_error;
        }
    }

    extern void irq_0(void);
    extern void irq_1(void);

    uint32_t irq_base = (uint32_t)irq_0;
    const uint32_t irq_size_w_error = ((uint32_t)irq_1) - ((uint32_t)irq_0);
    uint32_t irq_offset = irq_base;

    // setup irqs
    for(i = 0; i < 16 ; i++) {
        idt[i + 32].type = 0xE; //32 bit interrupt gate
        idt[i + 32].p = 1;
        idt[i + 32].s = 0;
        idt[i + 32].seg_sel = 0x8; //Segment selector
        idt[i + 32].offset15_0 = (uint16_t)(irq_offset);
        idt[i + 32].offset31_16 = (uint16_t)(irq_offset >> 16);
        irq_offset += irq_size_w_error;
    }

    uint32_t syscall_base = (uint32_t)syscall_handler;
    idt[0x80].type = 0xE;
    idt[0x80].p = 1;
    idt[0x80].s = 0;
    idt[0x80].seg_sel = 0x8;
    idt[0x80].offset15_0 = (uint16_t)(syscall_base);
    idt[0x80].offset31_16 = (uint16_t)(syscall_base >> 16);

    // prepare idtr
    idtr.limit = (VECTORS * sizeof(struct idt_desc)) - 1;
    idtr.base = (uint32_t)&idt;

    load_idtr(idtr);

    enable_interrupts();
}

void common_handler_error_code(struct context_w_error context)
{

halt: goto halt;

}

void common_handler(struct context_no_error context)
{

halt: goto halt;

}
