#include <stdint.h>
#include <string.h>
#include "mm.h"
#include "pmm.h"
#include "boot.h"

// RECURSIVE_PD_VIRTUAL is the address where pdir was mapped
#define RECURSIVE_PD_VIRTUAL 0xFFFFF000
#define RECURSIVE_PT_BASE 0xFFC00000

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

    // Recursive paging to be able to add page tables through virtual address
    pdir[1023] = (uint32_t)pdir | PAGE_PRESENT | PAGE_RW;
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

void mm_map_page(uint32_t va, uint32_t pa, uint32_t flags)
{
    uint32_t pd_index = va >> 22;
    uint32_t pt_index = (va >> 12) & 0x03FF;

    uint32_t *pd = (uint32_t *)RECURSIVE_PD_VIRTUAL;

    if (!(pd[pd_index] & PAGE_PRESENT)) {
        uint32_t new_table_physical = (uint32_t)pmm_frame_alloc();
        pd[pd_index] = new_table_physical | PAGE_PRESENT | PAGE_RW;
        uint32_t *new_pt_virtual = (uint32_t *)(RECURSIVE_PT_BASE + (pd_index * FRAME_SIZE));

        __asm__ volatile("invlpg (%0)" :: "r"((uint32_t)new_pt_virtual) : "memory");
        memset(new_pt_virtual, 0, FRAME_SIZE);
    }

    uint32_t *pt = (uint32_t *)(RECURSIVE_PT_BASE + (pd_index * FRAME_SIZE));

    pt[pt_index] = (pa & ~0xFFF) | flags;

    __asm__ volatile("invlpg (%0)" :: "r"(va) : "memory");
}

void mm_alloc_at(uint32_t va, uint32_t flags)
{
    uint32_t pa = (uint32_t)pmm_frame_alloc();
    mm_map_page(va & ~0xFFF, pa, flags);
}

void mm_alloc_region_at(uint32_t va, uint32_t size, uint32_t flags)
{
    uint32_t aligned_va = va & ~0xFFF;
    uint32_t aligned_va_end = (va + size + 0xFFF) & ~0xFFF;

    for (uint32_t current_va = aligned_va; current_va < aligned_va_end; current_va += FRAME_SIZE) {
        uint32_t pa = (uint32_t)pmm_frame_alloc();
        mm_map_page(current_va, pa, flags);
    }
}

void mm_unmap_page(uint32_t va)
{
    uint32_t pd_index = va >> 22;
    uint32_t pt_index = (va >> 12) & 0x03FF;

    uint32_t *pd = (uint32_t *)RECURSIVE_PD_VIRTUAL;

    if (!(pd[pd_index] & PAGE_PRESENT))
        return;

    uint32_t *pt= (uint32_t *)(RECURSIVE_PT_BASE + (pd_index * FRAME_SIZE));
    pt[pt_index] = 0;

    __asm__ volatile("invlpg (%0)" :: "r"(va) : "memory");
}
