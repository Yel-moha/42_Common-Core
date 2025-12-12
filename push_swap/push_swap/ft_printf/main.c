#include "ft_printf.h"
#include <stdio.h>

int main()
{
    ft_printf("Char: %c\n", 'A');
    printf("Char: %c\n", 'A');

    ft_printf("String: %s\n", "Hello");
    printf("String: %s\n", "Hello");

    ft_printf("Pointer: %p\n", &main);
    printf("Pointer: %p\n", &main);

    return 0;
}