#include <stdint.h>
#include "interrupts.h"

#define VECTORS 255

struct idt_desc idt[VECTORS];
struct idt_register idtr;

void load_idt(void)
{
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
