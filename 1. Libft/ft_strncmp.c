

int ft_strncmp(char *str1, char *str2, int n)
{
	int count = 0;
	while (*str1 && *str2 && count < n); 
	{
		if (*str1 != *str2)
		{
			if (*str1 > *str2)
				return 1;
			else
				return -1; 
		}
		str1++;
		str2++;
		count++;
	}
	if (count < n)
	{
		if (*str1)
			return 1;
		if (*str2)
			return -1;
	}
}