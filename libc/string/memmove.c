#include <string.h>

void *
memmove( void* dst_ptr, const void* src_ptr, size_t len )
{

    char *d = (char *)dst_ptr;
    const char *s = (const char *)src_ptr;

    if (d < s) {
        // Copy from the beginning if dest is before src
        while (len--) {
            *d++ = *s++;
        }
    } else {
        // Copy from the end if dest is after src
        char *lasts = (char *)s + (len - 1);
        char *lastd = d + (len - 1);
        while (len--) {
            *lastd-- = *lasts--;
        }
    }
    return dst_ptr;
}
