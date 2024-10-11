/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:23:16 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/11 16:23:23 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * Compares the first 'n' bytes of memory area 'ptr1' and memory area 'ptr2'.
 * 
 * @param ptr1 Pointer to the first memory area.
 * @param ptr2 Pointer to the second memory area.
 * @param n Number of bytes to compare.
 * 
 * @return An integer less than, equal to,
	or greater than zero if the first 'n' bytes of
 *         'ptr1' is found, respectively, to be less than, to match,
	or be greater than the
 *         first 'n' bytes of 'ptr2'.
 */
int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)ptr1;
	p2 = (const unsigned char *)ptr2;
	while (n--)
	{
		if (*p1 != *p2)
		{
			return ((int)(*p1 - *p2));
		}
		p1++;
		p2++;
	}
	return (0);
}
