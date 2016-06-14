#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#include <stdint.h>
#include <kernel/queue.h>

#define KEYBOARD_DEQUEUE(c) dequeue(keyboard_buffer, c)

#define KEYBOARD_ENQUEUE(c) enqueue(keyboard_buffer, c)

/*
 * Ascii map
 */
#define K_BKSP      0x08
#define K_TAB       0x09
#define K_ENTR      0x0A
#define K_ESC       0x1b
#define K_DEL       0x7f

/*
 * Special key code
 */
#define K_CTRL      0x80
#define K_SHFT      0x81
#define K_ALT       0x82
#define K_CAPS      0x83

#define K_INS       0x84
#define K_HOME      0x85
#define K_END       0x86
#define K_PGUP      0x87
#define K_PGDN      0x88
#define K_UP        0x89
#define K_DOWN      0x8a
#define K_LEFT      0x8b
#define K_RGHT      0x8c

#define K_F1        0x90
#define K_F2        0x91
#define K_F3        0x92
#define K_F4        0x93
#define K_F5        0x94
#define K_F6        0x95
#define K_F7        0x96
#define K_F8        0x97
#define K_F9        0x98
#define K_F10       0x99
#define K_F11       0x9a
#define K_F12       0x9b

queue_t keyboard_buffer;

static const char key_map[] = {
	0,      K_ESC,  '1',    '2',    '3',    '4',    '5',    '6',
	'7',    '8',    '9',    '0',    '-',    '=',    K_BKSP, K_TAB,
	'q',    'w',    'e',    'r',    't',    'y',    'u',    'i',
	'o',    'p',    '[',    ']',    K_ENTR, K_CTRL, 'a',    's',
	'd',    'f',    'g',    'h',    'j',    'k',    'l',    ';',
	'\'',   '`',    K_SHFT, '\\',   'z',    'x',    'c',    'v',
	'b',    'n',    'm',    ',',    '.',    '/',    K_SHFT, '*',
	K_ALT,  ' ',    K_CAPS, K_F1,   K_F2,   K_F3,   K_F4,   K_F5,
	K_F6,   K_F7,   K_F8,   K_F9,   K_F10,  0,      0,      K_HOME,
	K_UP,   K_PGUP, 0,      K_LEFT, 0,      K_RGHT, 0,      K_END,
	K_DOWN, K_PGDN, K_INS,  K_DEL,  K_F11,  K_F12
};

static const char shift_map[] = {
	0,      K_ESC,  '!',    '@',    '#',    '$',    '%',    '^',
	'&',    '*',    '(',    ')',    '_',    '+',    K_BKSP, K_TAB,
	'Q',    'W',    'E',    'R',    'T',    'Y',    'U',    'I',
	'O',    'P',    '{',    '}',    K_ENTR, K_CTRL, 'A',    'S',
	'D',    'F',    'G',    'H',    'J',    'K',    'L',    ':',
	'"',    '~',    0,      '|',    'Z',    'X',    'C',    'V',
	'B',    'N',    'M',    '<',    '>',    '?',    0,      '*',
	K_ALT,  ' ',    0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      K_HOME,
	K_UP,   K_PGUP, 0,      K_LEFT, 0,      K_RGHT, 0,      K_END,
	K_DOWN, K_PGDN, K_INS,  K_DEL,  0,      0
};

int handle_key(uint8_t);

#endif
