#include <stdio.h>

#if defined(__is_myos_kernel)
#include <kernel/tty.h>
#endif

int
putchar(int ic)
{
#if defined(__is_myos_kernel)
    char c = (char) ic;
    terminal_putchar(c);
#else
    // TODO: You need to implement a write system call.
#endif
    return ic;
}
