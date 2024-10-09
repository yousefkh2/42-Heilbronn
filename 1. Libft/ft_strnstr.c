#include <stddef.h> // For size_t

char *strnstr(const char *haystack, const char *needle, size_t len) {
    // If needle is an empty string, return haystack
    if (*needle == '\0') {
        return (char *)haystack;
    }

    size_t i = 0;

    // Iterate over haystack up to 'len' characters
    while (haystack[i] != '\0' && i < len) {
        // If current character matches the first character of needle
        if (haystack[i] == needle[0]) {
            size_t j = 1;

            // Initialize a variable to track the position in haystack
            size_t k = i + 1;

            // Compare the subsequent characters
            while (needle[j] != '\0' && k < len && haystack[k] == needle[j]) {
                j++;
                k++;
            }

            // If we've reached the end of needle, a match is found
            if (needle[j] == '\0') {
                return (char *)&haystack[i];
            }
        }
        i++;
    }

    // If no match is found, return NULL
    return NULL;
}

#include <stdio.h>

int main() {
    const char *text = "Hello, World!";
    const char *search = "World";
    char *result = strnstr(text, search, 12); // Limit search to first 12 characters

    if (result)
        printf("Found '%s' at position: %ld\n", search, result - text);
    else
        printf("'%s' not found within the first 12 characters.\n", search);

    return 0;
}
