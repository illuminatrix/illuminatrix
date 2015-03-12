#include <kernel/driver.h>
#include <kernel/interrupt_handler.h>
#include <stdio.h>

static int ps2_init();

struct driver ps2_drv __driver_entry = {
    "PS2/Keyboard", // Name
    ps2_init        // init function
};

int ps2_init()
{
    printf("I'm a driver loading\n");
    return 0;
}
