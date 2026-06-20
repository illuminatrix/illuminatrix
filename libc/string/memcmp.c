#include <string.h>

int
memcmp( const void * a_ptr, const void * b_ptr, size_t len )
{
    const unsigned char *l = a_ptr, *r = b_ptr;
    for (; len && *l == *r; len--, l++, r++);
    return len ? *l - *r : 0;
}
