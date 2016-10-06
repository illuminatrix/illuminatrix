#ifndef _ASM_UTILS_H
#define _ASM_UTILS_H

#define INVAL_INT 0xFF

#define ENTRY(name) \
    .text; .globl name; .type name,@function; name:

#define SAVE_ALL \
    pushl   %ds; \
    pushl   %es; \
    pushl   %fs; \
    pushl   %gs; \
    pushal;

#define RESTORE_ALL \
    popal; \
    popl    %gs; \
    popl    %fs; \
    popl    %es; \
    popl    %ds;

#endif
