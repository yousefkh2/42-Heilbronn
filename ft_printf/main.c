#include "ft_printf.h"

int main() {
    ft_printf("Hello, World!\n");
    ft_printf("Character: %c\n", 'A');
    ft_printf("String: %s\n", "Test string");
    ft_printf("Pointer: %p\n", (void *)main);
    ft_printf("Integer: %d\n", 12345);
    ft_printf("Unsigned: %u\n", 12345U);
    ft_printf("Hex (lowercase): %x\n", 0x1a3f);
    ft_printf("Hex (uppercase): %X\n", 0x1A3F);
    ft_printf("Percent: %%\n");
    return 0;
}
