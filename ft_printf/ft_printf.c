/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:12:12 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/15 22:36:40 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_format(const char **format, va_list args)
{
	int	printed_chars;

	printed_chars = 0;
	if (**format == 'c')
		printed_chars += handle_char(args);
	else if (**format == 's')
		printed_chars += handle_string(args);
	else if (**format == 'p')
		printed_chars += handle_pointer(args);
	else if (**format == 'd' || **format == 'i')
		printed_chars += handle_int(args);
	else if (**format == 'u')
		printed_chars += handle_unsigned(args);
	else if (**format == 'x' || **format == 'X')
		printed_chars += handle_hex(args, **format);
	else if (**format == '%')
		printed_chars += ft_putchar('%');
	else
	{
		printed_chars += ft_putchar('%');
		printed_chars += ft_putchar(**format);
	}
	(*format)++;
	return (printed_chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_chars;
	int		result;

	printed_chars = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			result = handle_format(&format, args);
			if (result == -1)
			{
				va_end(args);
				return (-1);
			}
			printed_chars += result;
		}
		else
		{
			result = ft_putchar(*format);
			if (result == -1)
			{
				va_end(args);
				return (-1);
			}
			printed_chars += result;
			format++;
		}
	}
	va_end(args);
	return (printed_chars);
}

