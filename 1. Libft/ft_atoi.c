/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:54:11 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/07 19:54:13 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int ft_atoi(const char *str)
{
	int sign = 1;
	int result = 0;

	while (*str == ' ' || *str == '\t' || *str == '\n') 
	{
	str++;
	}
	if (*str == '-' || *str == '+') {
		if (*str == '-') {
		sign = -1;
	}
	str++;
}
	while (*str && ft_isdigit(*str)) 
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return sign * result;
}