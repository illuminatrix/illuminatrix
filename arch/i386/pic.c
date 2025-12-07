#include "pic.h"

/* PIC Ports */
#define PIC1_DATA 0x21  /* Data port for master */
#define PIC2_DATA 0xA1  /* Data port for slave */
#define PIC1_CMD 0x20   /* Command port for master */
#define PIC2_CMD 0xA0   /* Command port for slave */

/* PIC Commands */
#define PIC_CMD_ICW4 0x01      /* If set(1), the PIC expects to recieve IC4 during initialization. */
#define PIC_CMD_SINGLE 0x02    /* If set(1), only one PIC in system. If cleared, PIC is cascaded with slave PICs, and ICW3 must be sent to controller. */
#define PIC_CMD_INTERVAL4 0x04 /* If set (1), CALL address interval is 4, else 8. This is useually ignored by x86, and is default to 0 */
#define PIC_CMD_LEVEL 0x08     /* If set (1), Operate in Level Triggered Mode. If Not set (0), Operate in Edge Triggered Mode */
#define PIC_CMD_INIT 0x10      /* Initialization bit. Set 1 if PIC is to be initialized */

// new pic offsets
#define PIC1_INT_OFFSET 0x20
#define PIC2_INT_OFFSET 0x28

// PIC Interrupts for Cascaded PICs
#define PIC_IRQ_SLAVE_CONNECTION 0x04
#define PIC_IRQ_CASCADE_MASTER_NUMBER 0x02

// PIC Final Initialization Commands
#define PIC_CMD_8086_MODE 0x01
#define PIC_CMD_AUTO_AKW 0x02
#define PIC_CMD_BUF_SLAVE 0x08
#define PIC_CMD_BUF_MASTER 0x0C
#define PIC_CMD_SFNM 0x10

#define PIC_EOI 0x20

static inline uint8_t in(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

static inline void out(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "dN"(port));
}

void pic_init()
{

    // ICW1 initialize PICs
    out(PIC1_CMD, PIC_CMD_INIT | PIC_CMD_ICW4);
    out(PIC2_CMD, PIC_CMD_INIT | PIC_CMD_ICW4);

    // ICW2 Set PIC Offsets
    out(PIC1_DATA, PIC1_INT_OFFSET);
    out(PIC2_DATA, PIC2_INT_OFFSET);

    // ICW3 Inform PICs which is Master and which Slave
    out(PIC1_DATA, PIC_IRQ_SLAVE_CONNECTION);       // Let Master PIC know where the Slave PIC is located
    out(PIC2_DATA, PIC_IRQ_CASCADE_MASTER_NUMBER);  // Let Slave PIC what is its IRQ number of the Master PIC

    // ICW4 Finallize PIC Initialization
    out(PIC1_DATA, PIC_CMD_8086_MODE | PIC_CMD_AUTO_AKW);
    out(PIC2_DATA, PIC_CMD_8086_MODE | PIC_CMD_AUTO_AKW);

    asm volatile ("sti");
}

void pic_enable_irq(uint8_t irq)
{
    uint16_t mask;
    uint16_t val;
    if (irq > 15) return;

    if (irq & 0x08) {
        mask = in(PIC2_DATA);
        val = mask & ~(1 << (irq & 0x07));
        out(PIC2_DATA, val);
    } else {
        mask = in(PIC1_DATA);
        val = mask & ~(1 << irq);
        out(PIC1_DATA, val);
    }
}

void pic_disable_irq(uint8_t irq)
{
    if (irq > 15) return;

    if (irq < 8) out(PIC1_DATA, ~(1 << irq));
    else out(PIC2_DATA, ~(1 << (irq - 8)));
}
