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

	ljmp $0x08, $start32

.code32
start32:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss

        PRINT_STR_PMODE $pmode_hello_msg

	mov $0x8000, %esp // move the esp to a any place
halt:
	hlt
	jmp halt

.p2align 2
gdt:
	.quad 0x0000000000000000 // null descriptor
	.quad 0x00cf9a000000ffff // code descriptor type=execute/read
	.quad 0x00cf92000000ffff // data descriptor type=read/write
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
pmode_hello_msg:
        .ascii "Hello from protected mode!"
        .byte 0x0
