#include "get_next_line.h"

size_t ft_strlen(const char *s) {
    size_t len = 0;
    if (!s)
        return 0;
    while (s[len])
        len++;
    return len;
}
