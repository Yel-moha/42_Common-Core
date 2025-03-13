#include "ft_printf/libft/libft.h"
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
        check_duplicates(&stack);
        stack.sorted = temp_order(&stack);
        //check_int_overflow(&stack);
        //check_sorted(&stack);

    }
    else
        ft_putstr_fd("Error\n", 1);
    free(stack.a);
    free(stack.b);
    free(stack.sorted);
    return (0);
}