#include "ft_printf.h"

int print_pointer_recursive(unsigned long num)
{
	int len = 0;
	char *digits = "0123456789abcdef";

	if (num >= 16)
	{
		len += print_pointer_recursive(num / 16);
	}
	len += ft_putchar(digits[num % 16]);
	return len;

}

int handle_pointer(va_list args)
{
	void *ptr = va_arg(args, void *);
	unsigned long addr = (unsigned long)ptr;
	int len = 0;

	if (!ptr)
	{
		len += ft_putstr_fd("(nil)", 1);
		return len;
	}

	len += ft_putstr("0x");
	len += print_pointer_recursive(addr);
	return len;
}