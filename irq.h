#ifndef _IRQ_H_
#define _IRQ_H_

#include <stdint.h>

typedef void (*irq_handler_t)(void);

enum IRQ_REQUEST_ERROR {
    IRQ_REQUEST_ERROR_OK = 0,
    IRQ_REQUEST_ERROR_BUSY,
    IRQ_REQUEST_ERROR_INVALID,
};

uint8_t irq_request(uint8_t irq, irq_handler_t handler);
void irq_handler();

#endif
