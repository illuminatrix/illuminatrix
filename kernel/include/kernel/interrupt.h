#ifndef _KERNEL_INTERRUPT_H
#define _KERNEL_INTERRUPT_H

#include <stdint.h>

#define _INTERRUPTION_TABLE_LENGTH 51

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
void interrupt_handler(int);

typedef struct
{
	uint16_t offset_1;	// base low
	uint16_t selector;
	uint8_t zero;
	uint8_t type; 
	uint16_t offset_2;	// base high
} idt_desc_t;

void
load_idt();

#endif
