#ifndef PIO_H
#define PIO_H

#include <stdint.h>

uint8_t in(uint16_t port);
void out(uint16_t port, uint8_t val);

#endif
