/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:53:56 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/10 14:01:22 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stddef.h>
#include "libft.h"

void ft_bzero(void *s, size_t n)
{
	char *ptr = (char *)s;
	size_t i = 0;

	while (i < n)
	{	
		*ptr = 0;
		ptr++;
		i++;
	}
}