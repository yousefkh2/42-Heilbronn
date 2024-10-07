// I need to do it two more times.

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	if (!s)
		return NULL;
	
	//allocate memory
	char *result = (char *)malloc(len + 1); // for the null terminator

	if (!result)
		return NULL;
	//check if 'start' is beyond the string length
	size_t str_len = ft_strlen(s);
	if (start >= str_len)
	{
		result[0] = '\0';
		return result;
	}
	
	//we will need index navigating
	size_t i = 0;
	while (i < len && s[start + i])
	{
		result[i] = s[start + i];
		i++;
	}

	result[i] = '\0';
	return result;
}