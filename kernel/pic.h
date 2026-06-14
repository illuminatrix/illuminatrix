#ifndef PIC_H
#define PIC_H

#include <stdint.h>

void pic_init();
void pic_enable_irq(uint8_t irq);
void pic_disable_irq(uint8_t irq);

#endif
