// just some touches remain (not complete)


#include <stddef.h>

char *strnstr(const char *haystack, const char *needle, size_t len)

{
	int count = 0;
	char *strt_needle = needle;
	char *moving_haystack;
	char *returned_pointer = haystack;

	if (!*needle)
	{
		return haystack;
	}
	while (*haystack && count < len)
	{
		moving_haystack = haystack;

		if (*needle == *moving_haystack)
		{
			strt_needle = needle;
			returned_pointer = moving_haystack;
			while (*strt_needle == *moving_haystack)
			{
				strt_needle++;
				moving_haystack++;

				if (*strt_needle == '\0')
				{
				//return the needle in the haystack. it is a pointer in the haystack
				return returned_pointer;
				}
			}
		}
		
		haystack++;
		count++;
	}
	return NULL;
	
	//pointer to the first letter in needle (will move as long as they are equal) /
	// if false positive, will return again to the first letter (or make it two pointers?)
	//moving pointer on haystack 

}