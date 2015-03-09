#include <kernel/interrupt.h>
#include <kernel/interrupt_handler.h>
#include <kernel/port.h>
#include <stdio.h>
#include <stdint.h>

static idt_desc_t descriptor_table[_INTERRUPTION_TABLE_LENGTH];

void
general_interrupt_handler(int intno)
{
	int ret = call_IDT_handler(intno);
	if (ret != 0)
		printf("Error[%d]: intno: %d %s\n", ret, intno,str_IDT_error(ret) );

	_port_writeb(PIC_1_CTRL, 0x20);
	_port_writeb(PIC_2_CTRL, 0x20);
}

static inline void
set_interrupt_descriptor(int intno, void (*f)())
{
	descriptor_table[intno].offset_1 = (uint32_t)f;
	descriptor_table[intno].selector = 8;
	descriptor_table[intno].zero = 0;
	descriptor_table[intno].type = _INTERRUPT_GATE;
	descriptor_table[intno].offset_2 = (((uint32_t)f) >> 16)&0xFFFF;
}

static inline void
fill_idt()
{

	set_interrupt_descriptor(0, trap0);
	set_interrupt_descriptor(1, trap1);
	set_interrupt_descriptor(2, trap2);
	set_interrupt_descriptor(3, trap3);
	set_interrupt_descriptor(4, trap4);
	set_interrupt_descriptor(5, trap5);
	set_interrupt_descriptor(6, trap6);
	set_interrupt_descriptor(7, trap7);
	set_interrupt_descriptor(8, trap8);
	set_interrupt_descriptor(9, trap9);
	set_interrupt_descriptor(10, trap10);
	set_interrupt_descriptor(11, trap11);
	set_interrupt_descriptor(12, trap12);
	set_interrupt_descriptor(13, trap13);
	set_interrupt_descriptor(14, trap14);
	set_interrupt_descriptor(15, trap15);
	set_interrupt_descriptor(16, trap16);
	set_interrupt_descriptor(17, trap17);
	set_interrupt_descriptor(18, trap18);
	set_interrupt_descriptor(19, trap19);
	set_interrupt_descriptor(20, trap20);
	set_interrupt_descriptor(21, trap21);
	set_interrupt_descriptor(22, trap22);
	set_interrupt_descriptor(23, trap23);
	set_interrupt_descriptor(24, trap24);
	set_interrupt_descriptor(25, trap25);
	set_interrupt_descriptor(26, trap26);
	set_interrupt_descriptor(27, trap27);
	set_interrupt_descriptor(28, trap28);
	set_interrupt_descriptor(29, trap29);
	set_interrupt_descriptor(30, trap30);
	set_interrupt_descriptor(31, trap31);
	set_interrupt_descriptor(32, trap32);
	set_interrupt_descriptor(33, trap33);
	set_interrupt_descriptor(34, trap34);
	set_interrupt_descriptor(35, trap35);
	set_interrupt_descriptor(36, trap36);
	set_interrupt_descriptor(37, trap37);
	set_interrupt_descriptor(38, trap38);
	set_interrupt_descriptor(39, trap39);
	set_interrupt_descriptor(40, trap40);
	set_interrupt_descriptor(41, trap41);
	set_interrupt_descriptor(42, trap42);
	set_interrupt_descriptor(43, trap43);
	set_interrupt_descriptor(44, trap44);
	set_interrupt_descriptor(45, trap45);
	set_interrupt_descriptor(46, trap46);
	set_interrupt_descriptor(47, trap47);
	set_interrupt_descriptor(48, trap48);
	set_interrupt_descriptor(49, trap49);
	set_interrupt_descriptor(50, trap50);
}

static inline void
wait_out()
{
	uint32_t i;
	for (i = 0; i < 1000; i++);
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

	IDTR.length = _INTERRUPTION_TABLE_LENGTH * sizeof(idt_desc_t) - 1;
	IDTR.base = (uint32_t) descriptor_table;
	asm volatile ( "lidt %0" : : "m"(IDTR) );

	// Enable only keyboard interrupt
	_port_writeb(PIC_1_DATA, IRQ_MASK(IRQ1));
	_port_writeb(PIC_2_DATA, IRQ_MASK(NO_IRQ));

	enable_idt();
}
