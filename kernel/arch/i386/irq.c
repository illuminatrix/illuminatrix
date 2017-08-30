#include <stdint.h>
#include <kernel/irq.h>
#include "interrupt.h"
#include <kernel/io.h>

static IRQ_handler_t IRQ_handlers[_INTERRUPT_LENGTH];

int call_IRQ_handler(void * frame_p)
{
    uint8_t irq_no = ((trap_frame_t*)frame_p)->trapno;
    if (IRQ_handlers[irq_no] == 0)
        return INTERRUPT_NOT_SUPPORTED;
    IRQ_handlers[irq_no](frame_p);
    return 0;
}

int add_IRQ_handler(int irq_no, IRQ_handler_t handler)
{
    uint16_t mask = 0;
    uint16_t irq_val = 0;
    if (irq_no >= _INTERRUPT_LENGTH || irq_no < 0)
        return INVALID_INT_NO;
    
    if (IRQ_handlers[irq_no] != 0)
        return HANDLER_PREV_DEFINED;

    // bit 0000 1000 (0x08) is enabled when irq is in the seccond pic
    if (irq_no & 0x08) {
        mask = _inb(PIC_SLAVE_DATA);
        irq_val = 1 << (irq_no & 0x07);
        _outb(PIC_SLAVE_DATA, IRQ_MASK(irq_val) & mask);
    } else {
        mask = _inb(PIC_MASTER_DATA);
        irq_val = 1 << irq_no;
        _outb(PIC_MASTER_DATA, IRQ_MASK(irq_val) & mask);
    }

    IRQ_handlers[irq_no] = handler;
    return 0;
}

void rm_IRQ_handler(int irq_no)
{
    IRQ_handlers[irq_no] = 0;
}

char *str_IRQ_error(int errno)
{
    return IRQ_error_str[errno];
}
