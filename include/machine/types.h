#ifndef __MACHINE_TYPES_H__
#define	__MACHINE_TYPES_H__

#if defined (__x86__)
#include "x86/types.h"
#else
#error architecture not supported
#endif

#endif  /* __MACHINE_TYPES_H__ */
