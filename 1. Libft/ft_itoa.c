#include "libft.h"
#include <stdlib.h>

int get_num_len(int n)
{
	int len = 0;

	if (n == 0)
		return 1;

	if (n < 0)
    {
        len++;  // for the '-' sign
        n = -n;  // work with absolute value
    }
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return len;
}

char *ft_itoa(int n)
{
	int len = get_num_len(n);
	char *str;
	long num = n;  // long to handle INT_MIN

	str = (char *)malloc(len + 1);
	if (!str)
		return NULL;

	str[len] = '\0';

	if (n == 0)
	{
		str[0] = '0';
		return str;
	}

	//handle negative numbers
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}

	//convert digits from the end of the string backwards
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return str;
}