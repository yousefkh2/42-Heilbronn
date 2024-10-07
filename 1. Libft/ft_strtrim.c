#include <stddef.h>   // For size_t
#include <stdlib.h>   // For malloc
#include "libft.h"   // For ft_strlcpy


int is_in_set(char c, const char *set)
	{
		while (*set)
		{
			if (c == *set)
			{
				return 1;
			}
			set++;
		}
		return 0;
	}


char *ft_strtrim(char const *s1, char const *set)
{
	size_t start, end, len;

	if (!s1 || !set)
	{
		return NULL;
	}

	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
	{
		start++;
	}

	end = ft_strlen(s1);
	while (end > start && is_in_set(s1[end - 1], set))
	{
		end--;
	}
	len = end - start;
	char *trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
	{
		return NULL;
	}

	ft_strlcpy(trimmed_str, &s1[start], len + 1);
	return trimmed_str;
}