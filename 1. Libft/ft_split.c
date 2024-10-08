#include <stdbool.h>
#include "libft.h"
#include <stdlib.h>
#include <string.h>


static int count_words(const char *str, char delim) {
    int count = 0;
    int in_word = 0;

    while (*str) {
        if (*str != delim && in_word == 0) {
            in_word = 1;
            count++;
        } else if (*str == delim) {
            in_word = 0;
        }
        str++;
    }
    return count;
}

// Function to allocate a word and copy it from the original string
static char *allocate_word(const char *start, int length) {
    char *word = (char *)malloc((length + 1) * sizeof(char));
    if (!word) {
        return NULL; // If allocation fails
    }
    strncpy(word, start, length);
    word[length] = '\0';
    return word;
}

// The ft_split function itself
char **ft_split(const char *str, char delim) {
    if (!str) {
        return NULL;
    }

    int word_count = count_words(str, delim);
    char **result = (char **)malloc((word_count + 1) * sizeof(char *)); // +1 for the NULL terminator
    if (!result) {
        return NULL;
    }

    int word_index = 0;
    while (*str) {
        while (*str == delim) {
            str++; // Skip delimiters
        }

        if (*str) {
            const char *word_start = str;
            int word_length = 0;

            while (*str && *str != delim) {
                str++;
                word_length++;
            }

            result[word_index] = allocate_word(word_start, word_length);
            if (!result[word_index]) {
                // Handle allocation failure by freeing already allocated memory
                while (word_index >= 0) {
                    free(result[word_index]);
                    word_index--;
                }
                free(result);
                return NULL;
            }
            word_index++;
        }
    }
    result[word_index] = NULL; // NULL-terminate the result array

    return result;
}


// after we counted everything... what should we do?
// i know how to count words / now what else? 
// a function that you give the word and its len and it allocates its memory
// how? you allocate space + you copy the word into the space.
// so we count the number of words / allocate space for each word / allocate space for an array of a number of words (the main array)

// we count the words only to know the len of the array
// allocate space for the array

// skip delimiters


// identify the word's start (we started a while loop at this point)

// find out the len of the word
// allocate memory for the word

// copy the word into the allocated memory
// move on to the next word