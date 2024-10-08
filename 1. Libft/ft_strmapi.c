#include "libft.h"

char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	if (!s || !f)  // Check for null inputs
        return NULL;
	unsigned int i = 0;
	size_t len = ft_strlen(s);
	char *new_str = (char *)malloc(len); //why plus one?

	if (!new_str)
		return NULL;

	while (s[i])
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';

	return new_str;
}