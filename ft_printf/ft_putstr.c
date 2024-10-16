/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:20:04 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/16 19:32:36 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;
	int	len;
	int	result;

	i = 0;
	len = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		result = ft_putchar(str[i]);
		if (result == -1)
			return (-1);
		len += result;
		i++;
	}
	return (len);
}
