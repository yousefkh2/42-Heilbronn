char* ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (c == *str)
		{
			return str;
		}
		str++;
	}
	
	if (c == '\0')
	{
		return str;
	}
	return 0;
}