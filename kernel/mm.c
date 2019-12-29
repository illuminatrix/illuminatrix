#include <stdint.h>
#include "mm.h"

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

void init_mm(mmap_entry_t *mmap_addr, uint32_t len)
{
    mmap_entry_t *mmap = mmap_addr;

    setup_identity_paging();
    __asm__ volatile ("movl $0x1234, 0"); /* remove me */
}
