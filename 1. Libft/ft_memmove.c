#include <stddef.h>

void *memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    // Check if the memory areas overlap
    if (d == s) {
        // If source and destination are the same, no need to do anything
        return dest;
    }

    if (d < s) {
        // If destination is before source, copy forwards
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        // If destination is after source, copy backwards to prevent overwriting
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }

    return dest;
}