#include "libft.h"

void ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)  // Special case for the minimum value of int
	{
		write(fd, "-2147483648", 11);
		return;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);  // Output the negative sign
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);  // Recursive call to handle the rest of the digits
	ft_putchar_fd((n % 10) + '0', fd);  // Output the last digit
}
