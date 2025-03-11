#ifndef PUSH_SWAP_H
    #define PUSH_SWAP_H
#include "ft_printf/libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <stdlib.h>

typedef struct s_stack
{
    int *a;
    int *b;
    int size_a;
    int size_b;
    int size;
    int *sorted;
} t_stack;
void    take_input(int argc, char **argv, t_stack *stack);
int *inputs_array(int argc, char **argv);
//void    take_input(int argc, char **argv, t_stack *stack);
//void    check_input(int argc, char **argv, t_stack *stack);
//void    check_duplicates(t_stack *stack);
//void    check_int_overflow(t_stack *stack);
//void    check_sorted(t_stack *stack);
//void    init_stack(t_stack *stack);
//void    init_stack_a(t_stack *stack);
//void    init_stack_b(t_stack *stack);

#endif