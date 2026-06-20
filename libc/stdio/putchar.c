#include <stdio.h>
#include <stdint.h>

#include "syscall.h"

int
putchar(int ic)
{
    long res;
    res = syscall2(1, (long)&ic, 1);
    if (res >= 0)
	return (int) res;
    return -1;
}

