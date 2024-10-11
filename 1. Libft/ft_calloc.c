/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:34:50 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/11 17:37:24 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h> // For size_t
#include <stdlib.h> // For malloc, free

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	size_t	total_size;
	void	*ptr;

	total_size = num_elements * element_size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
