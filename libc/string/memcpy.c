#include <string.h>

#define __WORD_CHUNK_OFFSET(S, AS) ( S << AS )
#define __WORD_CALC_NUMBER(L, AS)  ( L >> AS )
#define __WORD_SIZE(AS)            ( __WORD_CHUNK_OFFSET(1, AS) )
#define __WORD_EDGE_ADDR(P, S, AS) ( (void *)((size_t)P + __WORD_CHUNK_OFFSET(S, AS)) )
#define __WORD_CHECK_PTR(P, AS)    ( (size_t)P % __WORD_SIZE(AS) == 0 )

#define WORD_I386_SHIFT           2
#define WORD_I386_CHUNK_OFFSET(S) __WORD_CALC_NUMBER(L, WORD_I386_SHIFT)
#define WORD_I386_CALC_NUMBER(L)  __WORD_CALC_NUMBER(L, WORD_I386_SHIFT)
#define WORD_I386_SIZE            __WORD_SIZE(WORD_I386_SHIFT)
#define WORD_I386_EDGE_ADDR(P, S) __WORD_EDGE_ADDR(P, S, WORD_I386_SHIFT)
#define WORD_I386_CHECK_PTR(P)    __WORD_CHECK_PTR(P, WORD_I386_SHIFT)

//!============================================================================
//!
//! \brief
//!    A bastard try of memcpy with optimizations for i386.
//!
//! \details
//!    This function is a bastard try to recreate memcpy functionality 
//!    by using aspects pretty i386 specific.
//!
//! \param [out]
//!    dst_ptr    destiny pointer where data of copy shall be copied.
//!
//!
//! \param [in]
//!    src_ptr    source pointer where data of copy shall be fetched.
//! \param [in]
//!    len        defines size of the buffer to be copied.
//!
//! \return
//!    void*       destination address is returned
static inline void *
memcpy_i386( void * dst_ptr, const void * src_ptr, const size_t len )
{
    size_t i = 0;
    size_t remanent = len % WORD_I386_SIZE;

    if ( WORD_I386_CHECK_PTR( src_ptr ) && WORD_I386_CHECK_PTR( dst_ptr ) )
    {
        const size_t chunks = WORD_I386_CALC_NUMBER( len );
        long * d = dst_ptr;
        const long * s = src_ptr;

        for ( ; i < chunks; i++ )
            d[i] = s[i];
    }

    if ( remanent )
    {
        /* This block was created to deal with the remanent */
        void * from_ptr = NULL;
        void * to_ptr = NULL;

        if ( i )
        {
            /* To retake where we left */
            from_ptr = WORD_I386_EDGE_ADDR( src_ptr, i );
            to_ptr = WORD_I386_EDGE_ADDR( dst_ptr, i );
        }
        else
        {
            /* When there was not at least one chunk */
            from_ptr = (void *)(src_ptr);
            to_ptr = dst_ptr;
            remanent = len;
        }

        asm volatile (
            "cld; rep; movsb" 
            : "+c" ( remanent ), "+S" ( from_ptr ), "+D" ( to_ptr )
            :
        );
    }

    return dst_ptr;
}


extern void *
memcpy_gen( void * restrict dst_ptr, const void * restrict src_ptr, size_t size )
{
    unsigned char * d = (unsigned char*) dst_ptr;
    const unsigned char * s = (const unsigned char*) src_ptr;
    for ( size_t i = 0; i < size; i++ )
        d[i] = s[i];

    return dst_ptr;
}

extern void *
memcpy( void* restrict dst_ptr, const void* restrict src_ptr, size_t len )
{
    return memcpy_i386( dst_ptr, src_ptr, len );
}
