/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:29:46 by ykhattab          #+#    #+#             */
/*   Updated: 2024/10/11 19:36:50 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, &s1[start], len + 1);
	return (trimmed_str);
}

// strchr instead of is_in_set()

// static int	is_in_set(char c, char const *set)
// {
// 	while (*set)
// 	{
// 		if (c == *set)
// 			return (1);
// 		set++;
// 	}
// 	return (0);
// }

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	const char	*start;
// 	const char	*end;
// 	char		*empty;
// 	size_t		trimmed_len;
// 	char		*trimmed_str;

// 	if (s1 == NULL || set == NULL)
// 		return (NULL);
// 	start = s1;
// 	end = s1 + ft_strlen(s1) - 1;
// 	while (*start && is_in_set(*start, set))
// 		start++;
// 	if (*start == '\0')
// 	{
// 		empty = malloc(1);
// 		if (empty)
// 			empty[0] = '\0';
// 		return (empty);
// 	}
// 	while (end > start && is_in_set(*end, set))
// 		end--;
// 	trimmed_len = end - start + 1;
// 	trimmed_str = malloc(trimmed_len + 1);
// 	if (trimmed_str == NULL)
// 		return (NULL);
// 	ft_strlcpy(trimmed_str, start, trimmed_len + 1);
// 	return (trimmed_str);
// }
