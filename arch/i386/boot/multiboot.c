#include "boot.h"
#include <stdio.h>
#include "multiboot.h"
#include "mm.h"

extern void kernel_main();

multiboot_info_t *mem_info;

void early_kernel(multiboot_info_t *mem_info_ptr)
{
    mem_info = mem_info_ptr;
    kernel_main();
}

char *boot_get_cmdline(void)
{
    return (char*)mem_info->cmdline;
}

static char *boot_get_memory_block_type_name(uint32_t type)
{
    switch (type) {
        case 1:  return "AVAILABLE";
        case 2:  return "RESERVED";
        case 3:  return "ACPI_RECLAIMABLE";
        case 4:  return "ACPI_NVS";
        case 5:  return "BAD_MEMORY";
        default: return "UNKNOWN";
    }
}

void boot_enable_empty_memory(void)
{
    mmap_entry_t *mmap = (mmap_entry_t*)mem_info->mmap_addr;

    printf("\nMEMORY MAPPING:\n");
    while ((uint32_t)mmap < mem_info->mmap_addr + mem_info->mmap_length) {
        uint32_t start_hi   = mmap->addr >> 32;
        uint32_t start_lo   = mmap->addr & 0xFFFFFFFF;
        uint32_t end_hi     = (mmap->addr + mmap->len) >> 32;
        uint32_t end_lo     = (mmap->addr + mmap->len) & 0xFFFFFFFF;
        uint32_t len_hi     = mmap->len >> 32;
        uint32_t len_lo     = mmap->len & 0xFFFFFFFF;

        printf("Start: 0x%x%08x - End: 0x%x%08x | Size: 0x%x%08x | Type: %s\n",
                start_hi, start_lo,
                end_hi, end_lo,
                len_hi, len_lo,
                boot_get_memory_block_type_name(mmap->type));

        mmap = (mmap_entry_t *) ((uint32_t)mmap + mmap->size + sizeof(mmap->size));
    }
    printf("\n");
}
