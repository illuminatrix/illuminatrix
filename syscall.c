#include <stdint.h>

uint32_t systemcall_table[255];
uint8_t pos = 0;


int
terminal_putchar(char c){
    uint16_t* t_buffer = (uint16_t*)0xb8000;
    t_buffer[pos] = (uint16_t)c | (uint16_t) 15 << 8;
    pos++;

    return 1;
}

int
sys_print(char *data, int data_length)
{
    int ret = 0;
    for ( int i = 0; i < data_length; i++ )
        ret += terminal_putchar((int) ((const unsigned char*) data)[i]);
    return ret;
}

void
syscall_init(void)
{
	systemcall_table[1] = (uint32_t)sys_print;
}
