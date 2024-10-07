int handle_char(va_list args)
{
    char c = (char)va_arg(args, int);
    ft_putchar(c);
    return 1;
}