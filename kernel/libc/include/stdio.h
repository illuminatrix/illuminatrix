#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int vsprintf(char*, const char* __restrict, va_list);
int putchar(int);
int puts(const char*);

int getchar();

#ifdef __cplusplus
}
#endif

#endif
