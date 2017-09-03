#ifndef __MACHINE_LIMITS_H__
#define	__MACHINE_LIMITS_H__

#if defined (__x86__)
#include "x86/types.h"
#else
#error architecture not supported
#endif

#endif  /* __MACHINE_LIMITS_H__ */
