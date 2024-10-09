#include <stddef.h>
#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{	
	size_t s_len;
    char *substr;

    if (!s)
        return NULL;

    s_len = ft_strlen(s);

    if (start >= s_len)
        return malloc(1); // Return an empty string

    // Adjust len if it exceeds the string length
    if (start + len > s_len)
        len = s_len - start;

    substr = (char *)malloc(len + 1);
    if (!substr)
        return NULL;

    ft_strlcpy(substr, s + start, len + 1);
    return substr;
}