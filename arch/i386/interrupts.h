#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

struct idt_register {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed, aligned(8)));

struct idt_desc {
    uint32_t offset15_0:16;
    uint32_t seg_sel:16;
    uint32_t rsvd:8;
    uint32_t type:4;
    uint32_t s:1;
    uint32_t dpl:2;
    uint32_t p:1;
    uint32_t offset31_16:16;
};


struct context_no_error {
    uint32_t vector;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
};

struct context_w_error {
    uint32_t vector;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t error;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
};

void load_idt(void);

#define enable_interrupts() \
    __asm__ volatile("sti \n\t")

#define disable_interrupts() \
    __asm__ volatile("cli \n\t")

#define load_idtr(idt_ptr) \
    __asm__ volatile("lidtl %0 \n\t" \
                     :: "m" (idt_ptr))


#endif
