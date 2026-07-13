#include "boot.h"
#include "multiboot.h"

extern void kernel_main();

mmap_entry_t *mmap_first_entry;
uint32_t mmap_length;

multiboot_info_t *mem_info;

void early_kernel(multiboot_info_t *mem_info_ptr)
{
    mem_info = mem_info_ptr;
    mmap_first_entry = (mmap_entry_t *)mem_info_ptr->mmap_length;
    mmap_length = mem_info_ptr->mmap_length;

    kernel_main();
}

char *boot_get_cmdline(void)
{
    return (char*)mem_info->cmdline;
}
