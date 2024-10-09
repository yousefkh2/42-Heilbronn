#include <stddef.h>

int ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t count = 0;
	while (*str1 && *str2 && count < n)
	{
		if (*str1 != *str2)
		{
			return ((unsigned char)*str1 - (unsigned char)*str2);
		}
		str1++;
		str2++;
		count++;
	}
	if (count < n)
	{
		return ((unsigned char)*str1 - (unsigned char)*str2);
	}
	return 0;
}