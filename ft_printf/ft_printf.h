#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"

int ft_printf(const char *format, ...);
void ft_putchar(char c);
int handle_char(va_list args);
int handle_string(va_list args);
int handle_pointer(va_list args);
int handle_int(va_list args);
int handle_unsigned(va_list args);
int handle_hex(va_list args, char specifier);

#endif
