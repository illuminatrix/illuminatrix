#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/port.h>
#include <kernel/interrupt.h>

void
kernel_early(void)
{
	terminal_initialize();
	load_idt();
}

void
kernel_main(void)
{
	printf("Hello, kernel World!\n");

	int inter = are_interrupts_enabled();
	if (inter)
		printf("Interrupts available!\n");
}
