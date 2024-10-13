/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:23:05 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/13 02:05:58 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer_recursive(unsigned long num)
{
	int		len;
	char	*digits;

	len = 0;
	digits = "0123456789abcdef";
	if (num >= 16)
	{
		len += print_pointer_recursive(num / 16);
	}
	len += ft_putchar(digits[num % 16]);
	return (len);
}

int	handle_pointer(va_list args)
{
	void *ptr = va_arg(args, void *);
	unsigned long addr = (unsigned long)ptr;
	int len = 0;

	if (!ptr)
	{
		len += ft_putstr("(nil)");
		return (len);
	}

	len += ft_putstr("0x");
	len += print_pointer_recursive(addr);
	return (len);
}