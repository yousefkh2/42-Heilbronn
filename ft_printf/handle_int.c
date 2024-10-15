/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:48:31 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/15 22:15:14 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int_recursive(int num)
{
	int	len;
	int result;

	len = 0;
	if (num == -2147483648)
		return (ft_putstr("-2147483648"));
	if (num < 0)
	{
		result = ft_putchar('-');
		if (result == -1)
			return -1;
		len += result;
		num = -num;
	}
	if (num >= 10)
	{
		result = print_int_recursive(num / 10);
		if (result == -1)
			return -1;
		len += result;
	}
	len += ft_putchar((num % 10) + '0');
	return (len);
}

int	handle_int(va_list args)
{
	int	num;

	num = va_arg(args, int);
	return (print_int_recursive(num));
}

// int	handle_int(va_list args)
// {
// 	int	num;

// 	num = va_arg(args, int);
// 	return (print_int_recursive(num));
// }

// #include <stdio.h>
// int main()
// {
// 	int n = print_int_recursive(123);
// 	printf("here it is: %i", n);
// }