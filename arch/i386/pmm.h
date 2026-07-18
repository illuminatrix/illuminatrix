#ifndef PMM_H
#define PMM_H

#include <stdint.h>

#define BITMAP_ENTRY_BITS 32
#define FRAME_SIZE 4096
#define MAX_PHYSICAL_MEMORY (4ULL * 1024 * 1024 * 1024)
#define TOTAL_FRAMES (MAX_PHYSICAL_MEMORY / FRAME_SIZE)
#define BITMAP_SIZE (TOTAL_FRAMES / BITMAP_ENTRY_BITS)

extern uint32_t frame_bitmap[BITMAP_SIZE];

#define BITMAP_SET(frame) \
    (frame_bitmap[(frame) / BITMAP_ENTRY_BITS] |= (1 << ((frame) % BITMAP_ENTRY_BITS)))

#define BITMAP_CLEAR(frame) \
        (frame_bitmap[(frame) / BITMAP_ENTRY_BITS] &= ~(1 << ((frame) % BITMAP_ENTRY_BITS)))

#define BITMAP_TEST(frame) \
        ((frame_bitmap[(frame) / BITMAP_ENTRY_BITS] >> ((frame) % BITMAP_ENTRY_BITS)) & 1)

void *pmm_frame_alloc(void);
void pmm_frame_free(void *addr);

#endif
