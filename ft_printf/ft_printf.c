#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static int	handle_format(va_list args, const char format)
{
    if (format == 'c')
        return (handle_char(va_arg(args, int)));
    else if (format == 's')
        return (handle_string(va_arg(args, char *)));
    else if (format == 'p')
        return (handle_pointer(va_arg(args, void *)));
    else if (format == 'd' || format == 'i')
        return (handle_integer(va_arg(args, int)));
    else if (format == 'u')
        return (handle_unsigned(va_arg(args, unsigned int)));
    else if (format == 'x' || format == 'X')
        return (handle_hex(va_arg(args, unsigned int), format));
    else if (format == '%')
        return (handle_char('%'));
    return (0);
}

int	ft_printf(const char *format, ...)
{
    va_list	args;
    int		printed;

    va_start(args, format);
    printed = 0;
    while (*format)
    {
        if (*format == '%' && *(format + 1))
        {
            format++;
            printed += handle_format(args, *format);
        }
        else
        {
            write(1, format, 1);
            printed++;
        }
        format++;
    }
    va_end(args);
    return (printed);
}