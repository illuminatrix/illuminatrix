#ifndef __X86_LIMITS_H__
#define __X86_LIMITS_H__

#define	SCHAR_MAX     127                 /* min value for a signed char */
#define	SCHAR_MIN     ( -128 )            /* max value for a signed char */

#define	UCHAR_MAX     255                 /* max value for an unsigned char */
#define	CHAR_MAX      SCHAR_MAX           /* max value for a char */
#define	CHAR_MIN      SCHAR_MIN           /* min value for a char */

#define	USHRT_MAX     65535               /* max value for an unsigned short */
#define	SHRT_MAX      32767               /* max value for a short */
#define	SHRT_MIN      ( -32768 )          /* min value for a short */

#define	UINT_MAX      0xffffffffU         /* max value for an unsigned int */
#define	INT_MAX       2147483647          /* max value for an int */
#define	INT_MIN       ( -INT_MAX-1 )     /* min value for an int */

#define	ULONG_MAX     0xffffffffUL        /* max value for an unsigned long */
#define	LONG_MAX      2147483647L         /* max value for a long */
					  /* min value for a long */
#define	LONG_MIN      ( -2147483647L-1L )

#define	SSIZE_MAX     INT_MAX             /* max value for a ssize_t */
#define	SIZE_T_MAX    UINT_MAX            /* max value for a size_t */

#endif  /* __X86_LIMITS_H__ */
