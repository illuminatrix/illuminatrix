#ifndef MM_H
#define MM_H

#include <stdint.h>

#define FRAME 0x1000 /* 4k */
#define DIR_SIZE 1<<10 /* 0x400 or 1024 entries */

typedef struct mmap_entry mmap_entry_t;

void turn_on_paging(void);
void init_mm(void);
void setup_identity_paging(void);

#endif /* MM_H */
