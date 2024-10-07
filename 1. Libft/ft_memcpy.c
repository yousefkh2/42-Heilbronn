/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourusername <youremail@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: YYYY/MM/DD HH:MM:SS by yourusername      #+#    #+#             */
/*   Updated: YYYY/MM/DD HH:MM:SS by yourusername     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies 'n' bytes from memory area 'src' to memory area 'dest'.
 * The memory areas must not overlap.
 *
 * @param dest Pointer to the destination array where the content is to be copied.
 * @param src Pointer to the source of data to be copied.
 * @param n Number of bytes to copy.
 *
 * @return A pointer to the destination string 'dest'.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				count;
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	count = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (count < n)
	{
		d[count] = s[count];
		count++;
	}
	return (dest);
}
