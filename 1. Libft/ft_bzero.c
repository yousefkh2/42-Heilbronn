#include <stddef.h>

void bzero(void *s, size_t n)
{
	char *ptr = (char *)s;
	size_t i = 0;

	while (i < n)
	{	
		*ptr = 0;
		ptr++;
		i++;
	}
}