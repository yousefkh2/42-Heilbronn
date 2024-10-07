#include <stddef.h>

void *ft_memmove(void *dest, const void *src, size_t n);
{
	unsigned char *d = (unsigned char *)dest;
	unsigned char *s = (unsigned char *)src;
	
	if (d < s)
	{
		while (n--)
	{
		*d++ = *s++;
	}
	}
	else if (s < d)
	{
		// add here the rest.. i left it so that you write it yourself
	}
}