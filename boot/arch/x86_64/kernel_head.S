// SPDX-License-Identifier: MIT

// Format:
// I dont know if there is an asmfmt, so for now, this is the format.
// .section
// <tab> all goes in the section
// label:
// <tab>: all goes in label

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
	mov $stack_top, %esp
	// Print OK to VGA buffer, Oxb8000 is the start of the adress
	movl $OK, 0xb8000
	// Halt and back halt in case of interuptions?
1:	hlt
	jmp 1b


// Prints `ERR: <al>` and the given error code to screen and hangs.
// parameter: error code (in ascii) in al
// Usage:
//	mov $'1', %al
//	jmp error
error:
	movl $0x4f524f45, 0xb8000
	movl $0x4f3a4f52, 0xb8004
	movl $0x4f204f20, 0xb8008
	mov %al, 0xb800a
	hlt

.section .bss
	// The stack on x86 is recommened to be 16-byte aligned.
	// This is specially required for SSE instructions.
	// Note that for embedded embedded this could be much stack size.
	// https://medium.com/@_neerajpal/explained-difference-between-x86-x64-disassembly-49e9678e1ae2
	.align 16
	// 16k.
	.set STACKSIZE, 0x4000
stack_bottom:
	.skip STACKSIZE
stack_top:
