#include <kernel/driver.h>
#include <kernel/irq.h>
#include <kernel/keyboard.h>
#include <kernel/io.h>
#include <stdio.h>

#define _PS2_K_IRQ 0x09

#define _PS2_K_IN_PORT 0x60

static int ps2_init();
static void key_interrupt_handler(void*);

struct driver ps2_drv __driver_entry = {
    "PS2/Keyboard", // Name
    ps2_init        // init function
};

int
ps2_init()
{

    int error = add_IRQ_handler(_PS2_K_IRQ, key_interrupt_handler);
    if (error)
        printf("Error[%d]: %s", error, str_IRQ_error(error));
    return error;
}

void
key_interrupt_handler(void* trap_frame )
{
    uint8_t key_code;

    key_code = _inb(_PS2_K_IN_PORT);
    handle_key(key_code);
}
