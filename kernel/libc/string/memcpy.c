#include <string.h>


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
    return memmove( dst_ptr, src_ptr, len );
}
