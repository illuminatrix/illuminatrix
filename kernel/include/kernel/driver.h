#ifndef _KERNEL_DRIVER_H
#define _KERNEL_DRIVER_H

struct driver {
    const char *name;
    int (*init)();
};
typedef struct driver *driver_t;

#define __driver_entry __attribute__ ((section(".driver_stack")))

extern struct driver __driver_stack[], __driver_stack_end;

void driver_init();

#endif
