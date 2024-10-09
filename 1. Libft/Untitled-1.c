#include "libft.h"
#include <stddef.h>

char *strnstr(const char *haystack, const char *needle, size_t len) {
	if (*needle == '\0')
	{
		return (char *)haystack;
	}
	size_t i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0]) {
			size_t j = 1;
			size_t k = i + 1;

			while (needle[j] != '\0' && k < len && haystack[k] == needle[j])
			{
				j++;
				k++;
			}
			if (needle[j] == '\0')
			{
				return (char *)&haystack[i]
			}
		}
	}
}