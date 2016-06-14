#include <kernel/driver.h>
#include <kernel/interrupt.h>
#include <stdio.h>

#define _SERIAL_INTERRUPT 0x0C

static int uart_init();
void serial_interrupt_handler(int);

struct driver uart_drv __driver_entry = {
    "serial/uart", // Name
    uart_init      // init function
};

int
uart_init()
{
    uint8_t error =
        add_IDT_handler(_SERIAL_INTERRUPT, serial_interrupt_handler);
    if (error) {
        printf("Error[%d]: %s", error, str_IDT_error(error));
        return error;
    }
    
    return error;
}

void
serial_interrupt_handler(int intno )
{
    printf("%d", intno);
}
