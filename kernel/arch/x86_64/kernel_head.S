.code32

	.section .bss
	.align 16
stack_bottom:
	.skip 16384
stack_top:

	.section .text
	.global _start
	.type _start, @function
_start:
	mov $stack_top, %esp
	push %ebx
	movl $0x2f4b2f4f, 0xb8000
1:	hlt
	jmp 1b

	.size _start, . - _start
