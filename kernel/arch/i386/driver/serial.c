#include <kernel/driver.h>
#include <kernel/irq.h>
#include <stdint.h>
#include <stdio.h>
#include "../interrupt.h"

#define _SERIAL_IRQ 0x04

static int uart_init();
void serial_interrupt_handler(void*);

struct driver uart_drv __driver_entry = {
    "serial/uart", // Name
    uart_init      // init function
};

int
uart_init()
{
    uint8_t error =
        add_IRQ_handler(_SERIAL_IRQ, serial_interrupt_handler);
    if (error) {
        printf("Error[%d]: %s", error, str_IRQ_error(error));
        return error;
    }
    
    return error;
}

void
serial_interrupt_handler(void* trap_frame)
{
    printf("%d", ((trap_frame_t*)trap_frame)->trapno);
}
