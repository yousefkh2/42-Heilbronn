#include <stddef.h>

void *memchr(const void *ptr, int value, size_t n)
{
	size_t limit = 0;
	const unsigned char *p = (const unsigned char *)ptr;


	while (limit < n)
	{
		if (p[limit] == (unsigned char)value)
			return (void *)&p[limit];
		limit++;
	}
	return NULL;
}