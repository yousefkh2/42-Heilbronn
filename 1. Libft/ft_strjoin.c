

char *ft_strjoin(char const *s1, char const *s2)
{
	//get total length
	int len = 0;
	int count = 0;
	const char *temp_s1 = s1;
	const char *temp_s2 = s2;

	while (*temp_s1++)
	{
		len++;
	}
	while (*temp_s2++)
	{
		len++;
	}

	char *result = (char *)malloc(len + 1);
	if (!result)
		return NULL;
	
	// actually start joining them
	int i = 0;

	while (*s1)
	{
		result[i++] = *s1++;

	}
	while (*s2)
	{
		result[i++] = *s2++;
	}
	result[i] = '\0';
	return result;

}