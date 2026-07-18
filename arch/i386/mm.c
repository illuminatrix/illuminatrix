#include <stdint.h>
#include "mm.h"
#include "pmm.h"
#include "boot.h"

extern mmap_entry_t *mmap_first_entry;
extern uint32_t mmap_length;

uint32_t pdir[DIR_SIZE] __attribute__((aligned(FRAME)));
uint32_t pt[DIR_SIZE]   __attribute__((aligned(FRAME)));

uint32_t frame_bitmap[BITMAP_SIZE];

void setup_identity_paging(void)
{
    uint32_t i;

    /* set first pte's to first directory */
    pdir[0] = ((uint32_t) pt) | 0x3;  /* present | r/w | supervisor bits */

    /* fill DIR_SIZE page tables */
    for(i = 0; i < DIR_SIZE; i++)
        pt[i] = (i * FRAME) | 0x3; /* present | supervisor bits */

    turn_on_paging();
}

void init_mm(void)
{
    setup_identity_paging();
    boot_enable_empty_memory();
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

        for (int j = 0; j < 32; j++) {
            uint32_t index = (i * 32) + j;
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
