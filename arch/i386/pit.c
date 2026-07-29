#include <stddef.h>

#include "pit.h"
#include "irq.h"
#include "pio.h"

#define PIT_CHANNEL0 0x40
#define PIT_CMD_PORT 0x43

#define PIT_CMD_16BITS_MODE         0b0
#define PIT_CMD_SQUARE_WAVE_MODE    (0b011 << 1)
#define PIT_CMD_LOW_HI_ADDRESS_MODE (0b11 << 4)
#define PIT_CMD_CHANNEL_0           (0b00 << 6)

#define PIT_BASE_FREQ 1193182

void pit_init(uint32_t freq, void (*callback)(void))
{
    uint32_t divisor = PIT_BASE_FREQ / freq;
    if (divisor > 0xFFFF)
        divisor = 0xFFFF;

    if (callback)
        irq_request(0, callback);

    out(PIT_CMD_PORT, PIT_CMD_16BITS_MODE |
                      PIT_CMD_SQUARE_WAVE_MODE |
                      PIT_CMD_LOW_HI_ADDRESS_MODE |
                      PIT_CMD_CHANNEL_0);
    out(PIT_CHANNEL0, (uint8_t)(divisor & 0xFF));
    out(PIT_CHANNEL0, (uint8_t)(divisor >> 8));
}
