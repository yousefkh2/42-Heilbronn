#include "ft_printf.h"

int print_int_recursive(int num)
{
	int len = 0;
	if (num < 0)
	{
		len += ft_putchar('-');
		if (num == -2147483648)
		{
			len += ft_putstr_fd("2147483648", 1);
			return len;
		}
			num = -num;
	}
	if (num >= 10)
	{
		len += print_int_recursive(num / 10);
	}
	len += ft_putchar((num % 10) + '0');
	return len;
}

int handle_int(va_list args)
{
	int num = va_arg(args, int);
	
	return print_int_recursive(num);
}