#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void
print(const char* data, size_t data_length)
{
    for ( size_t i = 0; i < data_length; i++ )
        putchar((int) ((const unsigned char*) data)[i]);
}

int
printf(const char* restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;
    size_t amount;
    bool rejected_bad_specifier = false;

    while ( *format != '\0' ) {
        if ( *format != '%' ) {
        print_c:
            amount = 1;
            while ( format[amount] && format[amount] != '%' )
                amount++;
            print(format, amount);
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format;

        if ( *(++format) == '%' )
            goto print_c;

        if ( rejected_bad_specifier ) {
        incomprehensible_conversion:
            rejected_bad_specifier = true;
            format = format_begun_at;
            goto print_c;
        }

        if ( *format == 'c' ) {
            format++;
            char c = (char) va_arg(parameters, int /* char promotes to int */);
            print(&c, sizeof(c));
        }
        else if ( *format == 's' ) {
            format++;
            const char* s = va_arg(parameters, const char*);
            print(s, strlen(s));
        }
        else if ( *format == 'd' ) {
            format++;
            char chr[] = "0123456789";
            int number = va_arg(parameters, int);
            int decr, tmp_num;

            if ( number < 0 ) {
                putchar(0x2D);
                number*=-1;
            }

            tmp_num = number;
            
            for (decr = 1; tmp_num != 0; decr = decr * 10) {
                tmp_num = tmp_num / 10;
            }    
    
            for (decr = decr / 10; decr != 0; decr = decr / 10) {
                putchar(chr[((number / decr) % 10)]);
            }
    
            if (number == 0) {
                putchar('0');
            }     
        }
        else {
            goto incomprehensible_conversion;
        }
    }

    va_end(parameters);

    return written;
}
