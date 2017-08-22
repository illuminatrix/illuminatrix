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
extern void *
memcpy( void * restrict dst_ptr, const void * restrict src_ptr, size_t len )
{
    size_t i = 0;
    size_t remanent = len % PACK_32_SIZE;

    if ( PACK_32_CHECK_PTR( src_ptr ) && PACK_32_CHECK_PTR( dst_ptr ) )
    {
        const size_t chunks = PACK_32_CALC_NUMBER( len );
        int * d = dst_ptr;
        const int * s = src_ptr;

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
            from_ptr = PACK_32_EDGE_ADDR( src_ptr, i );
            to_ptr = PACK_32_EDGE_ADDR( dst_ptr, i );
        }
        else
        {
            /* When there was not at least one chunk */
            from_ptr = (void *)(src_ptr);
            to_ptr = dst_ptr;
            remanent = len;
        }

        __asm__ __volatile__ (
            "cld; rep; movsb"
            : "+c" ( remanent ), "+S" ( from_ptr ), "+D" ( to_ptr )
            :
        );
    }

    return dst_ptr;
}
