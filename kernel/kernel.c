#include <stdint.h>
#include "kernel.h"
#include "interrupts.h"
#include "mm.h"

void welcome()
{
    char *message = "Illuminatrix Kernel!";
    uint16_t* t_buffer = (uint16_t*)0xb8000;
    uint8_t i = 0;
    for (i = 0; message[i] != 0; i++)
        t_buffer[i] = (uint16_t)message[i] | (uint16_t) 15 << 8;

}

void kernel_main(multiboot_info_t *mem_info_ptr)
{
    welcome();
    load_idt();
    init_mm((mmap_entry_t *)mem_info_ptr->mmap_addr,
            mem_info_ptr->mmap_length);
}
