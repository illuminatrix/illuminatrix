#ifndef _IRQ_H_
#define _IRQ_H_

#include <stdint.h>

typedef void (*irq_handler_t)(void);

enum IRQ_REQUEST_ERROR {
    IRQ_REQUEST_ERROR_OK = 0,
    IRQ_REQUEST_ERROR_BUSY,
    IRQ_REQUEST_ERROR_INVALID,
};

void irq_init();
uint8_t irq_request(uint8_t irq, irq_handler_t handler);
uint8_t irq_release(uint8_t irq);
void irq_handler();

#endif
