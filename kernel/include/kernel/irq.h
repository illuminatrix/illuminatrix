#ifndef _KERNEL_INTERRUPT_HANDLER_H
#define _KERNEL_INTERRUPT_HANDLER_H

typedef void (*IRQ_handler_t)(void*);

enum IRQ_error {
    INTERRUPT_NOT_SUPPORTED = 1,
    INVALID_INT_NO,
    HANDLER_PREV_DEFINED
};
typedef enum IRQ_error IRQ_error_t;

static char *IRQ_error_str[3] = {
    "Success",
    "Interrupt not supported",
    "Invalid interruption number",
    "Interruption handler previously defined"
};

int call_IRQ_handler(void *);

int add_IRQ_handler(int, IRQ_handler_t);

void rm_IRQ_handler(int);

char *str_IRQ_error(int);
#endif
