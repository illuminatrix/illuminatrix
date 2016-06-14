#include <kernel/keyboard.h>
#include <kernel/queue.h>
#include <stdio.h>

static uint8_t _shift;

static uint8_t _ctrl;

static uint8_t _alt;

uint8_t
non_char(char c, uint8_t released)
{
    uint8_t ret = c;
    switch (c) {
        case (char)K_SHFT:
            _shift = !_shift;
            break;
        case (char)K_CTRL:
            _ctrl = !_ctrl;
            break;
        case (char)K_ALT:
            _alt = !_alt;
            break;
        case (char)K_CAPS:
            if (!released)
                _shift = !_shift;
            break;

        /* Not implemented yet */
        case (char)K_INS:
        case (char)K_HOME:
        case (char)K_END:
        case (char)K_PGUP:
        case (char)K_PGDN:
        case (char)K_UP:
        case (char)K_DOWN:
        case (char)K_LEFT:
        case (char)K_RGHT:
        case (char)K_F1:
        case (char)K_F2:
        case (char)K_F3:
        case (char)K_F4:
        case (char)K_F5:
        case (char)K_F6:
        case (char)K_F7:
        case (char)K_F8:
        case (char)K_F9:
        case (char)K_F10:
        case (char)K_F11:
        case (char)K_F12:
            break;
        default:
            ret = 0;
            break;
    }

    return ret;
}

int
handle_key(uint8_t key_num)
{
    if (key_num & 0x80) {
        non_char(key_map[key_num ^ 0x80], 1);
    }
    else if (!non_char(key_map[key_num], 0)) {
        if (_shift)
            KEYBOARD_ENQUEUE(shift_map[key_num]);
        else
            KEYBOARD_ENQUEUE(key_map[key_num]);
    }
    return 0;
}
