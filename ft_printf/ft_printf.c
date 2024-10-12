/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:12:12 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/12 20:16:10 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_chars;

	printed_chars = 0;
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
				printed_chars += ft_putchar('%');
			else
			{
				// Handle invalid specifier
				printed_chars += ft_putchar('%');
				printed_chars += ft_putchar(*format);
			}
			format++;
		}
		else
		{
			printed_chars += ft_putchar(*format);
			format++;
		}
	}
	va_end(args);
	return (printed_chars);
}

