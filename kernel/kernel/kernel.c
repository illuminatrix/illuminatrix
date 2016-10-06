#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/io.h>
#include <kernel/cpu_setup.h>
#include <kernel/driver.h>
#include <kernel/uart.h>

void
kernel_early(void)
{
    terminal_initialize();
    driver_init();
    cpu_init();
}

void
kernel_main(void)
{
    init_serial();

    int inter = are_interrupts_enabled();
    if (inter)
        printf("Interrupts available!\n");
    printf("Welocome to myos\n");
    while(1) putchar(getchar());
}
