#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int
vsprintf(char* str, const char* restrict format, va_list args)
{
    int written = 0;
    size_t amount;
    bool rejected_bad_specifier = false;

    while ( *format != '\0' ) {
        if ( *format != '%' ) {
        copy_str:
            amount = 1;
            while ( format[amount] && format[amount] != '%' )
                amount++;
            memcpy(&str[written], format, amount);
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format;

        if ( *(++format) == '%' )
            goto copy_str;

        if ( rejected_bad_specifier ) {
        incomprehensible_conversion:
            rejected_bad_specifier = true;
            format = format_begun_at;
            goto copy_str;
        }

        char pad_char = ' ';
        if ( *format == '0' ) {
            pad_char = '0';
            format++;
        }

        int width = 0;
        while (*format >= '0' && *format <= '9') {
            width = (width * 10) + (*format - '0');
            format++;
        }

        if ( *format == 'c' ) {
            format++;
            char c = (char) va_arg(args, int /* char promotes to int */);
            memcpy(&str[written++], &c, sizeof(c));
        }
        else if ( *format == 's' ) {
            format++;
            const char* s = va_arg(args, const char*);
            memcpy(&str[written], s, strlen(s));
            written += strlen(s);
        }
        else if ( *format == 'd' ) {
            format++;
            char chr[] = "0123456789";
            int number = va_arg(args, int);
            int decr, tmp_num;

            if ( number < 0 ) {
                str[written++] = 0x2D;
                number*=-1;
            }

            tmp_num = number;

            for (decr = 1; tmp_num != 0; decr = decr * 10) {
                tmp_num = tmp_num / 10;
            }

            for (decr = decr / 10; decr != 0; decr = decr / 10) {
                str[written++] = chr[((number / decr) % 10)];
            }

            if (number == 0) {
                str[written++] = '0';
            }
        }
        else if ( *format == 'x' || *format == 'p' ) {
            char *chr = "0123456789ABCDEF";
            uint32_t number = va_arg(args, uint32_t);

            char tmp_buf[10];
            int tmp_len = 0;

            if (number == 0) {
                tmp_buf[tmp_len++] = '0';
            } else {
                int shift = 28;

                while (shift >= 0 && ((number >> shift) & 0xF) == 0)
                    shift -= 4;

                while (shift >= 0) {
                    tmp_buf[tmp_len++] = chr[(number >> shift) & 0xF];
                    shift -= 4;
                }
            }

            if (*format == 'p') {
                str[written++] = '0';
                str[written++] = 'x';
            }

            int pad_count = width - tmp_len;
            while (pad_count > 0 ) {
                str[written++] = pad_char;
                pad_count--;
            }

            for (int i = 0; i < tmp_len; i++)
                str[written++] = tmp_buf[i];
            format++;
        }
        else {
            goto incomprehensible_conversion;
        }
    }

    if (written > 0)
	    str[written++] = '\0';

    return written;
}
