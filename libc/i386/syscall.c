#include "syscall.h"

long syscall2(long sysnumb, long a, long b)
{
    long res;
    __asm__ volatile ("int $0x80"
	: "=a" (res)
	: "0" (sysnumb),
	"b" (a),
	"c" (b));
    return res;
}

