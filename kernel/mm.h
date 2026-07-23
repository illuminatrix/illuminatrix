#ifndef MM_H
#define MM_H

#include <stdint.h>
#include "pmm.h"

#ifndef FRAME_SIZE
#error "frame size is not defined"
#endif

#define PAGE_ENTRY_SIZE 1<<10 /* 0x400 or 1024 entries */

#define PAGE_PRESENT    0x1
#define PAGE_RW         0x2

typedef struct mmap_entry mmap_entry_t;

void turn_on_paging(void);
void init_mm(void);
void setup_identity_paging(void);

void mm_map_page(uint32_t va, uint32_t pa, uint32_t flags);
void mm_alloc_at(uint32_t va, uint32_t flags);
void mm_alloc_region_at(uint32_t va, uint32_t size, uint32_t flags);
void mm_unmap_page(uint32_t va);

#endif /* MM_H */
