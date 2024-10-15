/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:22:11 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/15 22:42:27 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_recursive(unsigned int num)
{
	int	len;
	int result;

	len = 0;
	if (num >= 10)
	{
		result = print_unsigned_recursive(num / 10);
		if (result == -1)
			return (-1);
		len += result;
	}
	len += ft_putchar((num % 10) + '0');
	return (len);
}

int	handle_unsigned(va_list args)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	return (print_unsigned_recursive(num));
}
