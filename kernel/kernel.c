#include <stdio.h>
#include "interrupt.h"
#include "mm.h"
#include "irq.h"
#include "ker_syscall.h"
#include "boot.h"
#include "kmalloc.h"
#include "pit.h"

void welcome()
{
    printf("Illuminatrix Kernel!\n\n");
    printf("CMDLINE: %s\n", boot_get_cmdline());
}

void print_tick()
{
    printf("tick\n");
}

void kernel_main(void)
{
    syscall_init();
    irq_init();
    load_idt();

    welcome();
    init_mm();
    heap_init();

    pit_init(100, print_tick);
}
