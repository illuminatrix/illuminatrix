#ifndef HW_IRQ_H
#define HW_IRQ_H

#include <stdint.h>

void hw_irq_init();
void hw_irq_enable_irq(uint8_t irq);
void hw_irq_disable_irq(uint8_t irq);

#endif
