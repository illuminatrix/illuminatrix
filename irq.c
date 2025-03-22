#include "irq.h"
#include <stdio.h>

irq_handler_t irq_handlers[32] = {0};

struct irq_frame
{
    uint8_t irq;
    uint8_t data;
};

uint8_t irq_request(uint8_t irq, irq_handler_t handler)
{
    if (irq >= 32)
        return IRQ_REQUEST_ERROR_INVALID;

    irq_handlers[irq] = handler;
    return IRQ_REQUEST_ERROR_OK;
}

void irq_handler(struct irq_frame *frame)
{
    if (frame->irq >= 32)
        return;

    irq_handlers[frame->irq]();
}
