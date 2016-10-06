#include <stdint.h>
#include <kernel/irq.h>
#include "interrupt.h"

static IRQ_handler_t IRQ_handlers[_INTERRUPT_LENGTH];

int call_IRQ_handler(int intno)
{
    if (IRQ_handlers[intno] == 0)
        return INTERRUPT_NOT_SUPPORTED;
    IRQ_handlers[intno](intno);
    return 0;
}

int add_IRQ_handler(int intno, IRQ_handler_t handler)
{
    if (intno >= _INTERRUPT_LENGTH || intno < 0)
        return INVALID_INT_NO;
    
    if (IRQ_handlers[intno] != 0)
        return HANDLER_PREV_DEFINED;

    IRQ_handlers[intno] = handler;
    return 0;
}

void rm_IRQ_handler(int intno)
{
    IRQ_handlers[intno] = 0;
}

char *str_IRQ_error(int errno)
{
    return IRQ_error_str[errno];
}
