/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:49:11 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/15 22:29:47 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_recursive(unsigned int num, int uppercase)
{
	int		len;
	int		result;
	char	*digits;

	if (uppercase)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	len = 0;
	if (num >= 16)
	{
		result = print_hex_recursive(num / 16, uppercase);
		if (result == -1)
			return -1;
		len += result;
	}
	result = ft_putchar(digits[num % 16]);
	if (result == -1)
		return -1;
	len += result;
	return (len);
}


int	handle_hex(va_list args, char specifier)
{
	unsigned int	num;
	int				uppercase;

	num = va_arg(args, unsigned int);
	if (specifier == 'X')
		uppercase = 1;
	else
		uppercase = 0;
	return (print_hex_recursive(num, uppercase));
}
