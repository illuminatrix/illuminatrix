#include <stdio.h>
#include "kernel.h"
#include "interrupt.h"
#include "mm.h"
#include "pic.h"
#include "irq.h"

void welcome()
{
    printf("Illuminatrix Kernel!");

}

void print_tick()
{
}

void kernel_main(multiboot_info_t *mem_info_ptr)
{
    extern void syscall_init(void);

    syscall_init();
    pic_init();
    load_idt();

    pic_enable_irq(0);
    irq_request(0, print_tick);

    welcome();
    init_mm((mmap_entry_t *)mem_info_ptr->mmap_addr,
            mem_info_ptr->mmap_length);
    while (1)
    {
        asm volatile("hlt");
    }
}
