void *memcpy(void *dest, void *src, size_t n)
{
	size_t count = 0;
	char *d = (char *)dest;
	const char *s = (const char *)src;
	
	while (count < n)
	{
		d[count] = s[count];
		count++;
	}
	return dest;
}