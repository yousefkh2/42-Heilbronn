/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:49:11 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/12 20:07:31 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_recursive(unsigned int num, int uppercase)
	//how does this uppercase parameter work? can you help me imagine it?
{
	int len = 0;
	char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
	if (num >= 16)
	{
		len += print_hex_recursive(num / 16, uppercase);
		len += print_hex_recursive(num % 16, uppercase);
	}
	else
	{
		len += ft_putchar(digits[num]);
	}
	return (len);
}

int	handle_hex(va_list args, char specifier)
{
	unsigned int num = va_arg(args, unsigned int);
	int uppercase = (specifier == 'X') ? 1 : 0;
	return (print_hex_recursive(num, uppercase));
}