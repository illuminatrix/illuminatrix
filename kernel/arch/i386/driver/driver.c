#include <kernel/driver.h>
#include <stdio.h>

void
driver_init()
{
    driver_t drv;
    for(drv = &__driver_stack[0]; drv != &__driver_stack_end;
            drv++) {
        if (drv->init) {
            printf("Starting \'%s\'\n", drv->name);
            if (drv->init())
                printf("Error starting \'%s\'\n", drv->name);
        }
    }
}
