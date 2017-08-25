#include <string.h>

int
memcmp( const void * a_ptr, const void * b_ptr, size_t len )
{
    int result = 1;

     __asm__ __volatile__ ( "      \
         cld; repe cmpsb;          \
         jecxz  2f;                \
         jle 1f;                   \
                                   \
         1:                        \
             negl (%[RES]);        \
         2:                        \
             movl $0, (%[RES]);"
         : "+c" ( len ), "+S" ( a_ptr ),  "+D" ( b_ptr )
         :  [RES] "r" ( &result )
     );

    return result;
}
