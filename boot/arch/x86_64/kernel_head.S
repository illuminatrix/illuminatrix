// SPDX-License-Identifier: MIT

.section .text
	.global _start
	// Set _start as a function to export to help to linker as this the starting point of the program
	.type _start, @function
	// Format for characters to be printed in VGA buffer
	// Bit 76543210
	//     ||||||||
	//     |||||^^^-fore colour
	//     ||||^----fore colour bright bit
	//     |^^^-----back colour
	//     ^--------back colour bright bit OR enables blinking Text
	.set OK, 0x2f4b2f4f
	//         |||||||| This is OK text formated for VGA buffer
	//         ||||||^^-- Character O
	//         ||||^^---- Color font
	//         ||^^------ Character K
	//         ^^-------- Character font

_start:
	// Print OK to VGA buffer, Oxb8000 is the start of the adress
	movl $OK, 0xb8000
	// Halt and back halt in case of interuptions?
1:	hlt
	jmp 1b
