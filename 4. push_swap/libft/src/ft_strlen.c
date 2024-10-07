int ft_strlen(char* str)
{
	int count = 0;
	while (*str)
	{
		count += 1;
		str++;

	}
	return count;
}