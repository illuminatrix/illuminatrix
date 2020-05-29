#include <stdint.h>
#include <stdio.h>
#include "kernel.h"
#include "interrupts.h"
#include "mm.h"

void welcome()
{
    printf("Illuminatrix Kernel!");

}

void kernel_main(multiboot_info_t *mem_info_ptr)
{
    welcome();
    load_idt();
    init_mm((mmap_entry_t *)mem_info_ptr->mmap_addr,
            mem_info_ptr->mmap_length);
}
