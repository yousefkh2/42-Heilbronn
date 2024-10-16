/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:47:42 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/16 19:33:30 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_char(va_list args)
{
	char	c;
	int		result;

	c = (char)va_arg(args, int);
	result = ft_putchar(c);
	if (result == -1)
		return (-1);
	return (result);
}
