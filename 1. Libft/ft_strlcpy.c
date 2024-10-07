#include <stddef.h>

size_t ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t remaining = size;
	size_t src_len = ft_strlen(src);

	if (size > 0)
	{
		while (*src && remaining > 1)
		{
			*dest++ = *src++;
			remaining--;
		}
		*dest = '\0';
	}
	return src_len;
}