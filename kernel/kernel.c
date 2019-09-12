#include <stdint.h>

char *message = "hello kernel";

void kernel_main()
{
    uint16_t* t_buffer = 0xb8000;
    uint8_t i = 0;
    for (i = 0; message[i] != 0; i++)
        t_buffer[i] = (uint16_t)message[i] | (uint16_t) 15 << 8;
}
