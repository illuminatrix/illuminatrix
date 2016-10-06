#include "interrupt.h"
#include <kernel/irq.h>
#include <kernel/io.h>
#include <stdio.h>
#include <stdint.h>

void
general_interrupt_handler(trap_frame_t* frame)
{
    int ret = call_IRQ_handler(frame->trapno);
    if (ret != 0)
        printf("Error[%d]: intno: %d %s\n", ret, frame->trapno,
                str_IRQ_error(ret) );

    _outb(PIC_MASTER_CTRL, 0x20);
    _outb(PIC_SLAVE_CTRL, 0x20);
}

void
general_trap_handler(trap_frame_t* frame)
{
    printf("trap #%d\n", frame->trapno);
    _outb(PIC_MASTER_CTRL, 0x20);
    _outb(PIC_SLAVE_CTRL, 0x20);
}

void
fill_idr()
{

}
