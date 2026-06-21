#include "kernel.h"

extern void kernel_main();

mmap_entry_t *mmap_first_entry;
uint32_t mmap_length;

void early_kernel(multiboot_info_t *mem_info_ptr)
{
    mmap_first_entry = (mmap_entry_t *)mem_info_ptr->mmap_length;
    mmap_length = mem_info_ptr->mmap_length;

    kernel_main();
}
