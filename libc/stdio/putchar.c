#include<stdio.h>
#include <stdint.h>

int
putchar(int ic)
{
    long res;
    __asm__ volatile ("int $0x80"
	: "=a" (res)
	: "0" (1),
	"b" ((long)(&ic)),
	"c" ((long)(1)));
    if (res >= 0)
	return (int) res;
    return -1;
}

