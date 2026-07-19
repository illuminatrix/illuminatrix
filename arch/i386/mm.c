#include <stdint.h>
#include <string.h>
#include "mm.h"
#include "pmm.h"
#include "boot.h"

#define PAGE_PRESENT    0x1
#define PAGE_RW         0x2

uint32_t *pdir;
uint32_t *pt;

uint32_t frame_bitmap[BITMAP_SIZE];

void setup_identity_paging(void)
{
    uint32_t i;

    pdir = (uint32_t*)pmm_frame_alloc();
    memset(pdir, 0, FRAME_SIZE);

    pt = (uint32_t*)pmm_frame_alloc();
    memset(pt, 0, FRAME_SIZE);

    for (uint32_t i = 0; i < PAGE_ENTRY_SIZE; i++) {
        uint32_t paddr = i * FRAME_SIZE;
        pt[i] = paddr | PAGE_PRESENT | PAGE_RW;
    }

    pdir[0] = (uint32_t)pt | PAGE_PRESENT | PAGE_RW;
}

void init_mm(void)
{
    boot_enable_empty_memory();
    setup_identity_paging();
    turn_on_paging();
    __asm__ volatile ("movl $0x1234, 0"); /* remove me */
}

void turn_on_paging(void)
{
    __asm__ volatile ("mov %0, %%eax\n\t"
                      "mov %%eax, %%cr3\n\t"
                      "mov %%cr0, %%eax\n\t"
                      "or $0x80000000, %%eax\n\t"
                      "mov %%eax, %%cr0\n"
                      :: "p" (pdir)
                      : "ax");
}

void *pmm_frame_alloc(void)
{
    for (uint32_t i = 0; i < BITMAP_SIZE; i++) {
        if (frame_bitmap[i] == 0xFFFFFFFF)
            continue;

        for (int j = 0; j < BITMAP_ENTRY_BITS; j++) {
            uint32_t index = (i * BITMAP_ENTRY_BITS) + j;
            if (!BITMAP_TEST(index)) {
                BITMAP_SET(index);
                return (void *)(index * FRAME_SIZE);
            }
        }
    }
    return 0;
}

void pmm_frame_free(void *addr)
{
    uint32_t frame = (uint32_t)addr / FRAME_SIZE;
    if (frame < TOTAL_FRAMES)
        BITMAP_CLEAR(frame);
}
