#ifndef __LIMITS_H__
#define	__LIMITS_H__

#if defined (__x86__)
#include "x86/types.h"
#else
#error architecture not supported
#endif

#endif  /* __LIMITS_H__ */
