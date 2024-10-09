#include <stddef.h>   // For size_t
#include <stdlib.h>   // For malloc
#include "libft.h"    // For ft_strlcpy, ft_strlen, ft_memcpy


static int is_in_set(char c, char const *set)
{
    while (*set)
    {
        if (c == *set)
            return 1;
        set++;
    }
    return 0;
}

char *ft_strtrim(char const *s1, char const *set)
{
    if (s1 == NULL || set == NULL)
        return NULL;

    const char *start = s1;
    const char *end = s1 + ft_strlen(s1) - 1;

    // Move start pointer to the first character not in set
    while (*start && is_in_set(*start, set))
        start++;

    if (*start == '\0')
    {
        char *empty = malloc(1);
        if (empty)
            empty[0] = '\0';
        return empty;
    }

    // Move end pointer to the last character not in set
    while (end > start && is_in_set(*end, set))
        end--;

    // Calculate the length of the trimmed string + allocate memory
    size_t trimmed_len = end - start + 1;
    char *trimmed_str = malloc(trimmed_len + 1);
    if (trimmed_str == NULL)
        return NULL;

    // Copy the trimmed substring into the new memory using ft_strlcpy
    ft_strlcpy(trimmed_str, start, trimmed_len + 1);

    return trimmed_str;
}
