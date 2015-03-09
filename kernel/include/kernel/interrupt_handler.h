#ifndef _KERNEL_INTERRUPT_HANDLER_H
#define _KERNEL_INTERRUPT_HANDLER_H

typedef void (*IDT_handler_t)(int);

enum IDT_error {
    INTERRUPT_NOT_SUPPORTED = 1,
    INVALID_INT_NO,
    HANDLER_PREV_DEFINED
};
typedef enum IDT_error IDT_error_t;

static char *IDT_error_str[3] = {
    "Success",
    "Interrupt not supported",
    "Invalid interruption number",
    "Interruption handler previously defined"
};

int call_IDT_handler(int);

int add_IDT_handler(int, IDT_handler_t);

void rm_IDT_handler(int intno);

char *str_IDT_error(int);
#endif
