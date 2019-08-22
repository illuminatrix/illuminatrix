.altmacro

.macro CLEAN
        mov $0x06, %ah // scrool active page up
        mov $0x7, %bh // attribute 7
        mov $0x0, %cx // column, row upper left corner of scroll
        mov $0x184f, %dx // column, lower right corner of scroll
        int $0x10
.endm

.macro RESET_CURSOR
        mov $0x02, %ah // set cursor video option
        mov $0x0, %dx // dh, dl = x, y position
        mov $0x0, %bh // page number
        int $0x10
.endm

.macro PRINT_STR s, len
        mov \len, %cx //string length
        mov $0x0007, %bx // BIOS attributes (page 0, attribute 7)
	mov \s, %bp // pointer to string
        mov $0x13, %ah // print string video option
        mov $0x01, %al // move cursor when print string
        int $0x10
.endm

.macro PRINT_STR_PMODE str  // This macro doesn't know where cursor is located when it is called,
        movw \str, %si      // other macros are needed to clean the screen, position cursor, etc.
        mov $0xb8000, %ebx
1:
        lodsb
        orb %al,%al
        jz 2f
        orl $0x0100, %eax
        movw %ax, (%ebx)
        add $2, %ebx
        jmp 1b
2:
.endm
