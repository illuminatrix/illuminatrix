#ifndef _UART_H
#define _UART_H

#include <stdint.h>

int8_t init_serial(void);
void write_serial(char a);
char read_serial(void);
#endif
