# Error code is pushed to the stack automatically by HW. See intel's system programing manual -  6.13 Error code

.macro ISR_ERROR_CODE vector
.global isr_\vector
isr_\vector:
        pushal
        mov $(\vector), %eax # push interrupt vector number to save state of which interrupt was triggered
        pushl %eax
        call common_handler_error_code
        addl $4, %esp        # discard error code pushed by the cpu hw
        popal
        addl $4, %esp        # discard interrupt vector number
        iretl
.endm

.macro ISR vector
.global isr_\vector
isr_\vector:
        pushal
        mov $(\vector), %eax # push interrupt vector number to save state of which interrupt was triggered
        pushl %eax
        call common_handler
        addl $4, %esp        # discard interrupt vector number
        popal
        iretl
.endm
# For reference see intel's system programing manual -  6.3.1 External interrupts
## interrupt_vectors
ISR                  0   # divide error
ISR                  1   # reserved
ISR                  2   # nmi
ISR                  3   # breakpoint
ISR                  4   # overflow
ISR                  5   # bound range exceeded
ISR                  6   # invalid opcode
ISR                  7   # no math coprocessor
ISR_ERROR_CODE       8   # double fault
ISR                  9   # coporcessor segment overrun
ISR_ERROR_CODE       10  # invalid tss
ISR_ERROR_CODE       11  # segment not present
ISR_ERROR_CODE       12  # stack segment fault
ISR_ERROR_CODE       13  # general protection
ISR_ERROR_CODE       14  # page fault
ISR                  15  # reserved
ISR                  16  # fpu error
ISR_ERROR_CODE       17  # alignment check
ISR                  18  # machine check
ISR                  19  # SIMD Floating-Point exception
ISR                  20  # Virtualization exception
ISR                  21
ISR                  22
ISR                  23
ISR                  24
ISR                  25
ISR                  26
ISR                  27
ISR                  28
ISR                  29
ISR                  30
ISR                  31

.global syscall_handler
syscall_handler:
	pushl %edx # param 3
	pushl %ecx # param 2
	pushl %ebx # param 1
	call *systemcall_table(,%eax,4) # call systemcall function position %eax moving 4 bytes
	add 12, %esp # cleaning stack
	# return is available in %eax
	iretl

