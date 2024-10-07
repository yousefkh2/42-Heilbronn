#include <stdio.h>
#include "libft.h"

int main(void) {
    char c = 'A';
    printf("Is %c an alphabetic character? %d\n", c, ft_isalpha(c));
    return 0;
}


#include <stdio.h>
// Include your header file
#include "libft.h"

int main(void)
{
    printf("ft_isalpha('A') = %d\n", ft_isalpha('A')); // Expected: 1
    printf("ft_isalpha('z') = %d\n", ft_isalpha('z')); // Expected: 1
    printf("ft_isalpha('5') = %d\n", ft_isalpha('5')); // Expected: 0
    printf("ft_isalpha('!') = %d\n", ft_isalpha('!')); // Expected: 0
    printf("ft_isalpha(128) = %d\n", ft_isalpha(128)); // Test with extended ASCII
    return 0;
}
