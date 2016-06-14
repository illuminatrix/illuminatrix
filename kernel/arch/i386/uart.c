#include <stdint.h>
#include <kernel/io.h>

#define _PS2_UART_PORT 0x3f8

int8_t 
init_serial(void)
{
    _outb(_PS2_UART_PORT + 1, 0x00);    // Disable all interrupts
    _outb(_PS2_UART_PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    _outb(_PS2_UART_PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    _outb(_PS2_UART_PORT + 1, 0x00);    //                  (hi byte)
    _outb(_PS2_UART_PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    _outb(_PS2_UART_PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    _outb(_PS2_UART_PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    _outb(_PS2_UART_PORT + 1, 0x01);    // Enable all interrupts
    
    return 0;
}

static int8_t
is_transmit_empty(void) {
    return _inb(_PS2_UART_PORT + 5) & 0x20;
}

static int8_t
serial_received() {
    return _inb(_PS2_UART_PORT + 5) & 1;
}

void
write_serial(char a)
{
    while (is_transmit_empty() == 0);
    _outb(_PS2_UART_PORT, a);
}

char
read_serial(void)
{
    while (serial_received() == 0);
    return _inb(_PS2_UART_PORT);
}
