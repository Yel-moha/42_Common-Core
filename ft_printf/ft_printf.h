#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>


int	ft_printf(const char *format, ...);

int handle_string(char *str);
int handle_integer(int n);
int	handle_char(char c);
int handle_hex(unsigned int value, char specifier);
int handle_unsigned(unsigned int value);
int handle_pointer(void *ptr);

#endif
