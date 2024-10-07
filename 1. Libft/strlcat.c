#include <stddef.h>
#include "libft.h"


//still not complete or done right
size_t strlcat(char *dst, const char *src, size_t size)
{
	
	size_t src_len = ft_strlen(src);
	size_t dst_len = ft_strlen(dst);

	char *d = dst;

	size_t remaining = size;
	if (remaining > 0)
	{
		while (*d)
		{
			d++;
		}
		while (remaining > 1 && *src)
		{
			*dst++ = *src++;
			remaining--;
		}
	}
	return src_len + dst_len - 1
}
