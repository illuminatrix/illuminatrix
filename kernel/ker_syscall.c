#include <stdint.h>
#include "pio.h"


#define VGA_TEXTMODE_ADDRESS 0xb8000
#define VGA_TEXTMODE_CLEAN_CHARACTER 0x20
#define VGA_TEXTMODE_WIDTH 80
#define VGA_TEXTMODE_HEIGHT 25

// VGA CRT Controller I/O Ports
#define VGA_TEXTMODE_CRTC_INDEX_PORT 0x3D4
#define VGA_TEXTMODE_CRTC_DATA_PORT  0x3D5

// VGA CRT Controller Internal Registers
#define VGA_TEXTMODE_CRTC_CURSOR_HIGH 0x0E
#define VGA_TEXTMODE_CRTC_CURSOR_LOW  0x0F

uint32_t systemcall_table[255];
uint16_t pos = 0;

void
terminal_update_cursor(void)
{
    out(VGA_TEXTMODE_CRTC_INDEX_PORT, VGA_TEXTMODE_CRTC_CURSOR_HIGH);
    out(VGA_TEXTMODE_CRTC_DATA_PORT, (uint8_t)((pos >> 8) & 0xFF));

    out(VGA_TEXTMODE_CRTC_INDEX_PORT, VGA_TEXTMODE_CRTC_CURSOR_LOW);
    out(VGA_TEXTMODE_CRTC_DATA_PORT, (uint8_t)(pos & 0xFF));
}

void
terminal_init(void)
{
    for (int x = 0; x < VGA_TEXTMODE_WIDTH * VGA_TEXTMODE_HEIGHT; x++) {
        uint16_t* t_buffer = (uint16_t*)VGA_TEXTMODE_ADDRESS;
        t_buffer[x] = (uint16_t)VGA_TEXTMODE_CLEAN_CHARACTER | (uint16_t) 15 << 8;
    }
    terminal_update_cursor();
}

int
terminal_putchar(char c){
    if (pos == 0)
        terminal_init();

    if (c == '\0' || c == '\r')
        return 1; // Ignore entirely

    if (c == '\n') {
        pos = ((pos + VGA_TEXTMODE_WIDTH) - (pos % VGA_TEXTMODE_WIDTH));
        terminal_update_cursor();
        return 1;
    }

    uint16_t* t_buffer = (uint16_t*)VGA_TEXTMODE_ADDRESS;
    t_buffer[pos] = (uint16_t)c | (uint16_t) 15 << 8;
    pos++;

    terminal_update_cursor();
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
