#include <stdio.h>
#include "interrupt.h"
#include "mm.h"
#include "pic.h"
#include "irq.h"
#include "ker_syscall.h"
#include "boot.h"
#include "kmalloc.h"

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
    heap_init();

    uint32_t *test_allocation = kmalloc(sizeof(uint32_t));
    *test_allocation = 1000;
    printf("test_allocation val %d\n", *test_allocation);
    printf("test_allocation address 0x%08x\n", test_allocation);

    kfree(test_allocation);

    uint32_t *test_allocation2 = kmalloc(sizeof(uint32_t));
    *test_allocation2 = 1000;
    printf("test_allocation val %d\n", *test_allocation2);
    printf("test_allocation address 0x%08x\n", test_allocation2);

    test_allocation = kmalloc(sizeof(uint32_t));
    *test_allocation = 1000;
    printf("test_allocation val %d\n", *test_allocation);
    printf("test_allocation address 0x%08x\n", test_allocation);


    kfree(test_allocation2);
    kfree(test_allocation);
}
