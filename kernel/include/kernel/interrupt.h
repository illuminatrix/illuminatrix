#ifndef _KERNEL_INTERRUPT_H
#define _KERNEL_INTERRUPT_H

///////////////////////////////////////////////////////////////////
// -- Common IRQ Table for x86 in Protected Mode
// IRQ NUMBWE	INTNO	Desctiption
// ----------------------------------------------------------------
// IRQ0			0x08	Timer
// IRQ1			0x09	Keyboard
// IRQ2			0x0A	Cascade for 8259A Slave controller
// IRQ3			0x0B	Serial port 2
// IRQ4			0x0C	Serial port 1
// IRQ5			0x0D	AT systems: Parallel Port 2. PS/2 systems: reserved
// IRQ6			0x0E	Diskette drive
// IRQ7			0x0F	Parallel Port 1
// IRQ8/IRQ0	0x70	CMOS Real time clock
// IRQ9/IRQ1	0x71	CGA vertical retrace
// IRQ10/IRQ2	0x72	Reserved
// IRQ11/IRQ3	0x73	Reserved
// IRQ12/IRQ4	0x74	AT systems: reserved. PS/2: auxiliary device
// IRQ13/IRQ5	0x75	FPU
// IRQ14/IRQ6	0x76	Hard disk controller
// IRQ15/IRQ7	0x77	Reserved
///////////////////////////////////////////////////////////////////

#include <stdint.h>

#define _INTERRUPTION_TABLE_LENGTH 51

// Type of interrupt descriptor
#define _INTERRUPT_GATE 0x8E
#define _TRAP_GATE 0x8F

// Software Port Map 
#define PIC_1_CTRL 0x20
#define PIC_2_CTRL 0xA0

#define PIC_1_DATA 0x21
#define PIC_2_DATA 0xA1

// IN-Service Register
// Primary Controller
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

void trap0(); void trap1(); void trap2(); void trap3(); void trap4();
void trap5(); void trap6(); void trap7(); void trap8(); void trap9();
void trap10(); void trap11(); void trap12(); void trap13(); void trap14();
void trap15(); void trap16(); void trap17(); void trap18(); void trap19();
void trap20(); void trap21(); void trap22(); void trap23(); void trap24();
void trap25(); void trap26(); void trap27(); void trap28(); void trap29();
void trap30(); void trap31(); void trap32(); void trap33(); void trap16();
void trap17(); void trap18(); void trap32(); void trap33(); void trap34();
void trap35(); void trap36(); void trap37(); void trap38(); void trap39();
void trap40(); void trap41(); void trap42(); void trap43(); void trap44();
void trap45(); void trap46(); void trap47(); void trap48(); void trap49();
void trap50();
void general_interrupt_handler(int);

struct idt_desc {
	uint16_t offset_1;	// base low
	uint16_t selector;
	uint8_t zero;
	uint8_t type; 
	uint16_t offset_2;	// base high
};
typedef struct idt_desc idt_desc_t;

void
load_idt();

static inline void
enable_idt()
{
	asm("sti");
}

#endif
