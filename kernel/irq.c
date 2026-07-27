#include <stddef.h>

#include "irq.h"
#include "hw_irq.h"

irq_handler_t irq_handlers[32] = {0};

struct irq_frame
{
    uint32_t irq;
    uint32_t data;
};

void irq_init()
{
    hw_irq_init();
}

uint8_t irq_request(uint8_t irq, irq_handler_t handler)
{
    if (irq >= 32)
        return IRQ_REQUEST_ERROR_INVALID;

    hw_irq_enable_irq(irq);

    irq_handlers[irq] = handler;
    return IRQ_REQUEST_ERROR_OK;
}

uint8_t irq_release(uint8_t irq)
{
    if (irq >= 32)
        return IRQ_REQUEST_ERROR_INVALID;

    hw_irq_disable_irq(irq);

    irq_handlers[irq] = NULL;
    return IRQ_REQUEST_ERROR_OK;

}

void irq_handler(struct irq_frame frame)
{
    if (frame.irq >= 32)
        return;

    irq_handlers[frame.irq]();
}
