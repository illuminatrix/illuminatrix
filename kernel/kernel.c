#include <stdio.h>
#include "interrupt.h"
#include "mm.h"
#include "pic.h"
#include "irq.h"
#include "ker_syscall.h"
#include "boot.h"

void welcome()
{
    printf("Illuminatrix Kernel!\n\n");
    printf("CMDLINE: %s\n", boot_get_cmdline());
}

void print_tick()
{
}

void kernel_main(void)
{
    syscall_init();
    pic_init();
    load_idt();

    pic_enable_irq(0);
    irq_request(0, print_tick);

    welcome();
    init_mm();
}
