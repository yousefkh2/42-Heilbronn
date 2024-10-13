/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:48:31 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/13 03:04:57 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int_recursive(int num)
{
	int	len;

	len = 0;
	if (num == -2147483648)
		return (ft_putstr("-2147483648"));
	if (num < 0)
	{
		len += ft_putchar('-');
		num = -num;
	}
	if (num >= 10)
		len += print_int_recursive(num / 10);
	len += ft_putchar((num % 10) + '0');
	return (len);
}

int handle_int(va_list args)
{
	int num = va_arg(args, int);
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