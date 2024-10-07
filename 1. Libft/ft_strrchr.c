char* ft_strrchr(char *str, int c)
{
	char *last_occurrence = 0;

	while (*str)
	{
		if (*str == c)
		{
			last_occurrence = str;
		}
		str++;
	}
	
	
	if (c == '\0')
	{
		return str;
	}
	return last_occurrence;
}