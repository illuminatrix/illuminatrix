#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/interrupt.h>
#include <kernel/driver.h>

void
kernel_early(void)
{
    terminal_initialize();
    driver_init();
    load_idt();
}

void
kernel_main(void)
{
    printf("Hello, kernel World!\n");

    int inter = are_interrupts_enabled();
    if (inter)
        printf("Interrupts available!\n");

    while(1) putchar(getchar());
}
