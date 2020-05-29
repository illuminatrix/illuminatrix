#include<stdio.h>
#include <stdint.h>

uint8_t pos = 0;


int
terminal_putchar(char c){
    uint16_t* t_buffer = (uint16_t*)0xb8000;
    t_buffer[pos] = (uint16_t)c | (uint16_t) 15 << 8;
    pos++;

    return 1;
}

int
putchar(int ic)
{
    char c = (char) ic;
    return terminal_putchar(c);
}

