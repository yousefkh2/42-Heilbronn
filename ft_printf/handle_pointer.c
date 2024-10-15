/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:23:05 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/15 23:13:01 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer_recursive(unsigned long num)
{
	int		len;
	int		result;
	char	*digits;

	len = 0;
	digits = "0123456789abcdef";
	if (num >= 16)
	{
		result = print_pointer_recursive(num / 16);
		if (result == -1)
			return (-1);
		len += result;
	}
	result = ft_putchar(digits[num % 16]);
	if (result == -1)
		return (-1);
	len += result;
	return (len);
}


int	handle_pointer(va_list args)
{
	void			*ptr;
	unsigned long	addr;
	int				len;
	int				result;

	ptr = va_arg(args, void *);
	addr = (unsigned long)ptr;
	len = 0;
	if (!ptr)
	{
		result = ft_putstr("0x0");
		if (result == -1)
			return (-1);
		len += result;
		return (len);
	}
	result = ft_putstr("0x");
	if (result == -1)
		return (-1);
	len += result;
	result = print_pointer_recursive(addr);
	if (result == -1)
		return (-1);
	len += result;
	return (len);
}

