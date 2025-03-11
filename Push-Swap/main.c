//#include "ft_printf/libft/libft.h"
//#include "ft_printf/ft_printf.h"

#include "push_swap.h"

int main(int argc, char **argv)
{
    t_stack stack;

    if (argc == 1)
        return (0);
    take_input(argc, argv, &stack);
    if (stack.a)
    {
        ft_putstr_fd(argv[1], 1);
        ft_putstr_fd("\n",1);
    }
    else
        ft_putstr_fd("Error\n", 1);
    return (0);
}