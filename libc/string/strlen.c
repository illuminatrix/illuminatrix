#include <string.h>

size_t
strlen( const char* s_ptr )
{
    const char *s = s_ptr;
    while (*s) {
        s++;
    }
    return s - s_ptr;
}
