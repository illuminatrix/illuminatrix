
#include <stdio.h>

#if defined(__is_myos_kernel)
#include <kernel/keyboard.h>
#endif

int
getchar()
{
    char c;
#if defined(__is_myos_kernel)
    while(buffer_dequeue(&c));
#else
    // TODO: You need to implement a write system call.
#endif
    return c;
}
