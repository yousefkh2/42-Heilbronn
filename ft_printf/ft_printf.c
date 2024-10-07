#include "ft_printf.h"



int ft_printf(const char *format, ...)
{
    va_list args;
    int	printed_chars = 0;

    va_start(args, format);


    
	while (*format)
{
    if (*format == '%')
    {
        format++;
		if (*format == 'c')
    		printed_chars += handle_char(args);
		else if (*format == 's')
    		printed_chars += handle_string(args);
		else if (*format == 'p')
			printed_chars += handle_pointer(args);
		else if (*format == 'd' || *format == 'i')
			printed_chars += handle_int(args);
		else if (*format == 'u')
			printed_chars += handle_unsigned(args);
		else if (*format == 'x' || *format == 'X')
			printed_chars += handle_hex(args, *format);
		else if (*format == '%')
			{
				ft_putchar('%');
				printed_chars++;
			}
			else
			{
				//Handle invalid specifier
				ft_putchar('%');
				ft_putchar(*format);
				printed_chars += 2;
			}
			format++;
	}
	else
	{
		ft_putchar(*format);
		printed_chars++;
		format++;
	}

    ; // Handle invalid specifier if necessary

}

	va_end(args);
	return printed_chars;
}