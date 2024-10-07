int count_words(char const *s, char c)
{
	int count = 0;
	int in_word = 0;

	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;

		} else if (*s == c)
		{
			in_word == 0;
		}
		s++;
	}
	return count;
}