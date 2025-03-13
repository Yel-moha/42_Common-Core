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
int check_input(char *argv, size_t j, int *array);
void    check_duplicates(t_stack *stack);
int *temp_order(t_stack *stack);
void    check_int_overflow(t_stack *stack);
int order_them(int *array, int size, int j, int i);
void sort_using_matrix(int *a, int size, int *sorted);
void sort_array(int *a, int size, int *sorted);
void apply_permutation(int **M, int *a, int *sorted, int size);
//void    take_input(int argc, char **argv, t_stack *stack);
//void    check_input(int argc, char **argv, t_stack *stack);
//void    check_duplicates(t_stack *stack);
//void    check_int_overflow(t_stack *stack);
//void    check_sorted(t_stack *stack);
//void    init_stack(t_stack *stack);
//void    init_stack_a(t_stack *stack);
//void    init_stack_b(t_stack *stack);

#endif