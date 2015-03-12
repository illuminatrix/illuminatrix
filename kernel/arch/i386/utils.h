#ifndef _ASM_UTILS_H
#define _ASM_UTILS_H

#define SAVE_ALL \
    cld; \
    pushl   %es; \
    pushl   %ds; \
    pushl   %eax; \
    pushl   %ebp; \
    pushl   %edi; \
    pushl   %esi; \
    pushl   %edx; \
    pushl   %ecx; \
    pushl   %ebx;

#define RESTORE_ALL \
    popl    %ebx; \
    popl    %ecx; \
    popl    %edx; \
    popl    %esi; \
    popl    %edi; \
    popl    %ebp; \
    popl    %eax; \
    popl    %ds; \
    popl    %es;

#endif
