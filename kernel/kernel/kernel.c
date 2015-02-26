#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/port.h>


char US_QWERTY_1[128]=
{
	// Key Presses
	'`',
	0,//Escape
	'1','2','3','4','5','6','7','8','9','0',
	'-','=',
	'\b','\t',//Backspace and Tab
	'q','w','e','r','t','y','u','i','o','p',
	'[',']',
	'\n',//Enter
	128,//Left Control
	'a','s','d','f','g','h','j','k','l',
	';','\'','`',
	127,//Left Shift
	'\\',
	'z','x','c','v','b','n','m',',','.',
	'/',
	127,//Right Shift
	'*',
	129,//Left Alt
	' ',//Spacebar
	0,//Capslock
	0,0,0,0,0,0,0,0,0,0,//F1 to F10
	0,//Number Lock
	0,//Scroll Lock

	//Number Pad with Number Lock:

	'7',//Home
	'8',//Up Arrow
	'9',//Page Up
	'-',//Number Pad Minus
	'4',//Left Arrow
	'5',//Number Pad 5
	'6',//Right Arrow
	'+',//Number Pad Plus
	'1',//End
	'2',//Down Arrow
	'3',//Page Down
	'0',//Insert           
	'.',//Delete
	0,0,0,//Absolutely Nothing
	0,0,// F11 and F12

	// Key Presses End
	0     // That's all

};

void kernel_early(void)
{
	terminal_initialize();
}

void kernel_main(void)
{
	printf ("Hello, kernel World!\n");
	for(;;)
	{
		_port_writeb(KEYBOARD_PORT_R, 0);
		uint8_t key;
		while (1)
		{
			key = _port_readb(KEYBOARD_PORT_R);
			if (key < 128 && US_QWERTY_1[key] != '\n' &&
					US_QWERTY_1[key] < 127)
				break;
		}
		putchar(US_QWERTY_1[key]);
	}
}
