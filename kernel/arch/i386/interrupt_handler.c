#include <kernel/interrupt_handler.h>
#include <kernel/interrupt.h>

static IDT_handler_t IDT_handlers[_INTERRUPTION_TABLE_LENGTH];

int call_IDT_handler(int intno)
{
    if (IDT_handlers[intno] == 0)
        return INTERRUPT_NOT_SUPPORTED;
    IDT_handlers[intno](intno);
    return 0;
}

int add_IDT_handler(int intno, IDT_handler_t handler)
{
    if (intno <= _INTERRUPTION_TABLE_LENGTH || intno < 0)
        return INVALID_INT_NO;
    
    if (IDT_handlers[intno] != 0)
        return HANDLER_PREV_DEFINED;

    IDT_handlers[intno] = handler;
    return 0;
}

void rm_IDT_handler(int intno)
{
    IDT_handlers[intno] = 0;
}

char *str_IDT_error(int errno)
{
    return IDT_error_str[errno];
}
