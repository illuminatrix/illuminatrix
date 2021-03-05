#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>

static void
print(const char* data, size_t data_length)
{
    for ( size_t i = 0; i < data_length; i++ )
        putchar((int) ((const unsigned char*) data)[i]);
}

int
printf(const char* restrict format, ...)
{
    int written = 0;
    char buffer[255];
    va_list parameters;
    va_start(parameters, format);

    written = vsprintf(&buffer[0], format, parameters);
    print(buffer, written);

    va_end(parameters);

    return written;
}
