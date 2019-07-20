#include "boot.h"

.code16
.globl start
start:
	cli
	# Set segments on Zero
	xor %ax, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss

	CLEAN
	RESET_CURSOR
	PRINT_STR $start_msg, $11

	PRINT_STR $gdt_msg, $11
	lgdt gdtdesc

	PRINT_STR $protecte_msg, $23
	mov %cr0, %eax
	mov $0x1, %eax
	mov %eax, %cr0

	PRINT_STR $jmp_cs_msg, $10
	ljmp $0x8, $start32

start32:
	mov $0xB, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss

	mov $0x8000, %esp // move the esp to a any place
halt:
	hlt
	jmp halt

.p2align 2
gdt:
	.word 0, 0
	.byte 0, 0, 0, 0
	.word (((0xffffffff) >> 12)&0xffff), ((0x0)&0xffff)
	.byte (((0x0) >> 16)&0xff), (0x90 | (0xa)), (0xC0 | (((0xffffffff) >> 28) & 0xf)), (((0x0) >> 24) & 0xff)
	.word (((0xffffffff) >> 12)&0xffff), ((0x0)&0xffff)
	.byte (((0x0) >> 16)&0xff), (0x90 | (0x2)), (0xC0 | (((0xffffffff) >> 28) & 0xf)), (((0x0) >> 24) & 0xff)
gdtdesc:
	.word (gdtdesc - gdt - 1)
	.long gdt

start_msg:
	.ascii "starting..."
gdt_msg:
	.ascii "setting gdt"
protecte_msg:
	.ascii "enabling protected mode"
jmp_cs_msg:
	.ascii "jump to cs"
