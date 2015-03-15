#include <kernel/driver.h>
#include <kernel/interrupt_handler.h>
#include <kernel/keyboard.h>
#include <kernel/io.h>
#include <stdio.h>

#define _PS2_K_INTERRUPT 9

#define _PS2_k_IN_PORT 0x60

static int ps2_init();
static void key_interrupt_handler(int);

struct driver ps2_drv __driver_entry = {
    "PS2/Keyboard", // Name
    ps2_init        // init function
};

int
ps2_init()
{

    int error = add_IDT_handler(_PS2_K_INTERRUPT, key_interrupt_handler);
    if (error)
        printf("Error[%d]: %s", error, str_IDT_error(error));
    return error;
}

void
key_interrupt_handler(int intno )
{
    uint8_t key_code;

    key_code = _inb(_PS2_k_IN_PORT);
    handle_key(key_code);
}
