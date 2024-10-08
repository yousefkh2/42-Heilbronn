#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
	if (!s1 || !s2)
        return NULL;

	int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);

	char *result = (char *)malloc(len1 + len2 + 1);
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