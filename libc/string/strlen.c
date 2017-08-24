#include <string.h>

size_t
strlen( const char* s_ptr )
{
    size_t result = 0;

    __asm__ __volatile__ ( "  \
        mov $1, %%ecx;        \
        neg %%ecx;            \
        xor %%eax, %%eax;     \
        cld; repne scasb;     \
        neg %%ecx;            \
        sub $2, %%ecx;        \
        mov %%ecx, %1;"
        : "+D" ( s_ptr ), "=r" ( result )
        :
    );

    return result;
}
