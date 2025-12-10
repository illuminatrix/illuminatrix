#include <stdint.h>

#include "pio.h"

uint8_t in(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

void out(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "dN"(port));
}
