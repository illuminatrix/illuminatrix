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
	.set PTE_SIZE, 8
_start:
	mov $stack_top, %esp

	call set_up_page_tables
	call print_ok
	call halt

print_ok:
	// Print OK to VGA buffer, Oxb8000 is the start of the adress
	movl $OK, 0xb8000
	ret

halt:
	// Halt and back halt in case of interuptions?
1:	hlt
	jmp 1b
	// This should not be reached: but just in case
	mov $'1', %al
	call error

set_up_page_tables:
	// We have 4 level page model
	// P4 -> P3 -> P2 (2MB size) -> Frame

	// Move the adress of pt3 to eax
	mov pt3, %eax
	// Set Page Table Entry attributes
	or 0b11, %eax
	//   ||
	//   |^----- PRESENT
	//   ^------ WRITABLE

	// Set eax (pt3 direction with attributes) in first entry of pt4
	mov %eax, (pt4)

	// At this moment we have:
	// pt4[0]   = PTE(adress(pt3[0]) ,WRITABLE, PRESENT)
	// pt3[...] = PTE(adress(NONE),NULL, NULL)
	// pt2[...] = PTE(adress(NONE),NULL, NULL)

	mov pt2, %eax
	or 0b11, %eax
	//   ||
	//   |^----- PRESENT
	//   ^------ WRITABLE

	// Set eax (pt2 direction with attributes) in first entry of pt3
	mov %eax, (pt3)
	// At this moment we have:
	// pt3[0] = PTE(adress(pt2[0]),WRITABLE, PRESENT)
	// pt4[0] = PTE(adress(pt3[0]) ,WRITABLE, PRESENT)

	mov $0, %ecx
.map_pt2_table:
	// ebx = 2M * i-th | PTE flags
	mov 0x200000, %eax
	mul %ecx
	// FIXME: https://sourceware.org/binutils/docs/as/Infix-Ops.html
	or 0b1000011, %eax
	//   |    ||
	//   |    |^----- PRESENT
	//   |    ^------ WRITABLE
	//   ^----------- HUGE PAGE/NULL: must be 0 in P1 and P4, creates a 1GiB page in P3, creates a 2MiB page in P2
	mov %eax, %ebx

	// eax= pt2 + ecx * PTE_SIZE : add i-th page mul by 8 as PTE are 8 byte sized
	mov %ecx, %eax
	// I dont know how to do mul $8, %eax: fails with Error: operand type mismatch for mul
	mov $PTE_SIZE, %edx
	mul  %edx
	add (pt2), %eax
	// pt2[i] = (2M*i | PTE flags)
	// *ebx = eax
	mov %eax, (%ebx)

	inc %ecx
	// Just map the first 512 Pages that is a lot
	cmpl $512, %ecx
	jne .map_pt2_table

	// At this moment we have:
	// pt2[i] = PTE(2MB* i, WRITABLE, PRESENT, HUGE PAGE) where i goes from 0 to 512, so 512 * 2 = 1G mapped
	// ^------PTE(adress(pt2)+i*8)
	// pt3[0] = PTE(adress(pt2[0]),WRITABLE, PRESENT)
	// pt4[0] = PTE(adress(pt3[0]) ,WRITABLE, PRESENT)

    ret


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
	.set PT_SIZE, 0x1000
	.set PT_ALIGNMENT, 0x1000
	.set STACKSIZE, 0x4000

	.comm pt4, PT_SIZE, PT_ALIGNMENT
	.comm pt3, PT_SIZE, PT_ALIGNMENT
	.comm pt2, PT_SIZE, PT_ALIGNMENT

	// The stack on x86 is recommened to be 16-byte aligned.
	// This is specially required for SSE instructions.
	// Note that for embedded embedded this could be much stack size.
	// https://medium.com/@_neerajpal/explained-difference-between-x86-x64-disassembly-49e9678e1ae2
	.align 16
	// 16k.
stack_bottom:
	.skip STACKSIZE
stack_top:
