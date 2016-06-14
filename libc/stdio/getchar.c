
#include <stdio.h>

#if defined(__is_myos_kernel)
#include <kernel/uart.h>
#endif

int
getchar()
{
    char c;
#if defined(__is_myos_kernel)
    while(c=read_serial());
#else
    // TODO: You need to implement a write system call.
#endif
    return c;
}
