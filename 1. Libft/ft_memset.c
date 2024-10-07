#include <stddef.h>
#include "libft.h"


void *ft_memset(void *s, int c, size_t n)

{
	unsigned char *ptr = (unsigned char *)s;
	size_t i = 0;

	while (i < n)
	{	
		*ptr = c;
		ptr++;
		i++;
	}

	return s;
}