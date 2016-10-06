#ifndef _KERNEL_INTERRUPT_H
#define _KERNEL_INTERRUPT_H

///////////////////////////////////////////////////////////////////
// -- IRQ Table for x86 8259A PIC Microcontroller --
//
// INTNO | IRQ NUMBER | Master Pin | Slave Pin | Desctiption
// ----------------------------------------------------------------
//  0x08   IRQ0         0000 0001    no-pin      Timer
//  0x09   IRQ1         0000 0010    no-pin      Keyboard
//  0x0A   IRQ2         0000 0100    no-pin      Cascade for 8259A Slave controller
//  0x0B   IRQ3         0000 1000    no-pin      Serial port 2
//  0x0C   IRQ4         0001 0000    no-pin      Serial port 1
//  0x0D   IRQ5         0010 0000    no-pin      AT systems: Parallel Port 2. PS/2 systems: reserved
//  0x0E   IRQ6         0100 0000    no-pin      Diskette drive
//  0x0F   IRQ7         1000 0000    no-pin      Parallel Port 1
//  0x70   IRQ8/IRQ0    no-pin       0000 0001   CMOS Real time clock
//  0x71   IRQ9/IRQ1    no-pin       0000 0010   CGA vertical retrace
//  0x72   IRQ10/IRQ2   no-pin       0000 0100   Reserved
//  0x73   IRQ11/IRQ3   no-pin       0000 1000   Reserved
//  0x74   IRQ12/IRQ4   no-pin       0001 0000   AT systems: reserved. PS/2: auxiliary device
//  0x75   IRQ13/IRQ5   no-pin       0010 0000   FPU
//  0x76   IRQ14/IRQ6   no-pin       0100 0000   Hard disk controller
//  0x77   IRQ15/IRQ7   no-pin       1000 0000   Reserved
///////////////////////////////////////////////////////////////////

#include <stdint.h>

#define _INTERRUPT_LENGTH 16

// 8259A Ports
#define PIC_MASTER_CTRL 0x20
#define PIC_SLAVE_CTRL 0xA0

#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_DATA 0xA1

// Type of interrupt descriptor
#define _INTERRUPT_GATE_TYPE 0xE
#define _TRAP_GATE_TYPE 0xF
#define _TASK_GATE_TYPE 0x5

// Descriptor privilege level
#define DPI_LVL_KERNEL 0
#define DPI_LVL_DEVICE_DRIVER_1 1
#define DPI_LVL_DEVICE_DRIVER_2 2
#define DPI_LVL_APPLICATIONS 3

// IN-Service Register
// Primary Controller
#define IRQ_ALL 0xFF
#define NO_IRQ 0x00
#define IRQ0 0x01
#define IRQ1 0x02
#define IRQ2 0x04
#define IRQ3 0x08
#define IRQ4 0x10
#define IRQ5 0x20
#define IRQ6 0x40
#define IRQ7 0x80

// Slave Controller
#define IRQ8 0x01
#define IRQ9 0x02
#define IRQ10 0x04
#define IRQ11 0x08
#define IRQ12 0x10
#define IRQ13 0x20
#define IRQ14 0x40
#define IRQ15 0x80

#define IRQ_MASK(irq) irq ^ 0xFF

#define IRQ_OFFSET 0x08

void trap_0(); void trap_1(); void trap_2(); void trap_3(); void trap_4();
void trap_5(); void trap_6(); void trap_7(); void trap_8(); void trap_9();
void trap_10(); void trap_11(); void trap_12(); void trap_13(); void trap_14();
void trap_15(); void trap_16(); void trap_17(); void trap_18();

void intr_0(); void intr_1(); void intr_2(); void intr_3(); void intr_4();
void intr_5(); void intr_6();void intr_7();void intr_8();void intr_9();
void intr_10(); void intr_11();void intr_12();void intr_13();void intr_14();
void intr_15();

struct trap_frame {
    //registers as pushed by pusha
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t oesp;      // useless & ignored
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    
    // rest of trap frame
    uint16_t gs;
    uint16_t padding1;
    uint16_t fs;
    uint16_t padding2;
    uint16_t es;
    uint16_t padding3;
    uint16_t ds;
    uint16_t padding4;
    uint32_t trapno;

    // below here defined by x86 hardware
    uint32_t err;
    uint32_t eip;
    uint16_t cs;
    uint16_t padding5;
    uint32_t eflags;

    // below here only when crossing rings, such as from user to kernel
    uint32_t esp;
    uint16_t ss;
    uint16_t padding6;
};
typedef struct trap_frame trap_frame_t;

void general_interrupt_handler(trap_frame_t*);
void general_trap_handler(trap_frame_t*);

struct idt_desc {
    uint16_t offset_1;   // base low
    uint16_t selector;   // interrupt function
    uint8_t zero;        // unused
    uint8_t type    :4 ; // type of interrupt
    uint8_t ss      :1 ; // storage segment
    uint8_t dpl     :2 ; // Descriptor privilege level
                         // (kernel=0, device_drivers=1, device_drivers=2, applications=3)
    uint8_t present :1 ; // 0 for unused interrupts
    uint16_t offset_2;   // base high
};
typedef struct idt_desc idt_desc_t;

void load_idt();

static inline void
enable_idt()
{
    asm("sti");
}

#endif
