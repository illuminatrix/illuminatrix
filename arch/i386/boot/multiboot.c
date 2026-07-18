#include "boot.h"
#include <stdio.h>
#include <string.h>
#include "multiboot.h"
#include "mm.h"
#include "pmm.h"

extern void kernel_main();

extern uint32_t __kernel_start;
extern uint32_t __kernel_end;

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
        case MMAP_MEMORY_AVAILABLE      :  return "AVAILABLE";
        case MMAP_MEMORY_RESERVED       :  return "RESERVED";
        case MMAP_MEMORY_ACPI_RECAIMABLE:  return "ACPI_RECLAIMABLE";
        case MMAP_MEMORY_NVS            :  return "ACPI_NVS";
        case MMAP_MEMORY_BADRAM         :  return "BAD_MEMORY";
        default                         : return "UNKNOWN";
    }
}

void boot_enable_empty_memory(void)
{
    mmap_entry_t *mmap = (mmap_entry_t*)mem_info->mmap_addr;

    memset(frame_bitmap, 0xFF, BITMAP_SIZE * sizeof(uint32_t));

    printf("\nPHISICAL MEMORY MAPPING:\n");
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

        if (mmap->type == MMAP_MEMORY_AVAILABLE) {
            uint32_t frame_start = (uint32_t)(mmap->addr / FRAME_SIZE);
            uint32_t frame_end = (uint32_t)((mmap->addr + mmap->len) / FRAME_SIZE);
            if (frame_end > BITMAP_SIZE)
                    frame_end = BITMAP_SIZE;
            for (uint32_t i = frame_start; i < frame_end; i++)
                    BITMAP_CLEAR(i);
        }

        mmap = (mmap_entry_t *) ((uint32_t)mmap + mmap->size + sizeof(mmap->size));
    }

    printf("\nKERNEL MEMORY INFORMATION:\n");
    printf("Start: 0x%08x - End: 0x%08x | Size: 0x%08x\n",
            &__kernel_start,
            &__kernel_end,
            &__kernel_end - &__kernel_start);

    uint32_t frame_kernel_end = ((uint32_t)&__kernel_end + FRAME_SIZE - 1) / FRAME_SIZE;
    for (uint32_t i = 0; i < frame_kernel_end; i++)
            BITMAP_SET(i);

    printf("\n");
}
