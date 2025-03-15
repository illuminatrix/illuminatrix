#include <string.h>

#define __PACK_CHUNK_OFFSET(S, AS) ( S << AS )
#define __PACK_CALC_NUMBER(L, AS)  ( L >> AS )
#define __PACK_SIZE(AS)            ( __PACK_CHUNK_OFFSET(1, AS) )
#define __PACK_EDGE_ADDR(P, S, AS) ( (void *)((size_t)P + __PACK_CHUNK_OFFSET(S, AS)) )
#define __PACK_CHECK_PTR(P, AS)    ( (size_t)P % __PACK_SIZE(AS) == 0 )

#define PACK_32_SHIFT           2
#define PACK_32_CHUNK_OFFSET(S) __PACK_CHUNK_OFFSET(S, PACK_32_SHIFT)
#define PACK_32_CALC_NUMBER(L)  __PACK_CALC_NUMBER(L, PACK_32_SHIFT)
#define PACK_32_SIZE            __PACK_SIZE(PACK_32_SHIFT)
#define PACK_32_EDGE_ADDR(P, S) __PACK_EDGE_ADDR(P, S, PACK_32_SHIFT)
#define PACK_32_CHECK_PTR(P)    __PACK_CHECK_PTR(P, PACK_32_SHIFT)


extern void *
memset( void * buf_ptr, int val, size_t len )
{
    size_t i = 0;
    const size_t chunks = PACK_32_CALC_NUMBER( len );
    size_t remanent = len % PACK_32_SIZE;
    unsigned int c = (unsigned char)val;
    void * dst_ptr = buf_ptr;

    c = (c << 8) | c;
    c = (c << 16) | c;

    for ( ; i < chunks; i++ )
        ( ( unsigned int * )dst_ptr )[i] = c;

    if ( remanent )
    {
        if ( i )
        {
            /* To retake where we left */
            dst_ptr =  PACK_32_EDGE_ADDR( buf_ptr, i );
        }
        else
        {
            /* When there was not at least one chunk */
            remanent = len;
        }

        while ( remanent-- )
        {
            ( ( unsigned char * )dst_ptr )[remanent] = val;
        }
    }

    return buf_ptr;
}
