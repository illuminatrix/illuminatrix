#ifndef MM_H
#define MM_H

#include "kernel.h"

#define FRAME 0x1000 /* 4k */
#define DIR_SIZE 1<<10 /* 0x400 or 1024 entries */

uint32_t pdir[DIR_SIZE] __attribute__((aligned(FRAME)));
uint32_t pt[DIR_SIZE]   __attribute__((aligned(FRAME)));

#define turn_on_paging()                                \
    __asm__ volatile ("mov %0, %%eax\n\t"               \
                      "mov %%eax, %%cr3\n\t"            \
                      "mov %%cr0, %%eax\n\t"            \
                      "or $0x80000000, %%eax\n\t"       \
                      "mov %%eax, %%cr0\n"              \
                      :: "p" (pdir)                     \
                      : "ax")

void init_mm(mmap_entry_t *, uint32_t);
void setup_identity_paging(void);

#endif /* MM_H */
