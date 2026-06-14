#ifndef MM_H
#define MM_H

#include <stdint.h>

#include "kernel.h"

#define FRAME 0x1000 /* 4k */
#define DIR_SIZE 1<<10 /* 0x400 or 1024 entries */

void turn_on_paging(void);
void init_mm(mmap_entry_t *, uint32_t);
void setup_identity_paging(void);

#endif /* MM_H */
