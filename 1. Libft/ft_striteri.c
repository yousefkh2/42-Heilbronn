#include "libft.h"

void ft_striteri(char *s, void (*f)(unsigned int, char*))
{
    if (!s || !f)
        return;
    
    unsigned int i = 0;
    
    while (s[i])
    {
        f(i, &s[i]); // Apply function f to each character
        i++;
    }
}
