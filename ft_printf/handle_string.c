int handle_string(va_list args)
{
    char *str = va_arg(args, char *);
	int len = 0;

	if (!str)
		str = "(null)";

	
	while (str[len])
	{
		ft_putchar(str[len]);
		len++;
	}
    return len;
}