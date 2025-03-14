#include "push_swap.h"

void free_all(t_stack *stack, int **M)
{
    int i;

    i = 0;
    if (M)
    {
        while (i < stack->size_a)
            free(M[i++]);
        free(M);
    }
    if (stack)
    {
        free(stack->a);
        free(stack->b);
        free(stack->sorted);
        free(stack);
    }
}

int main(int argc, char **argv)
{
    t_stack *stack;
    int **M;

    if (argc == 1)
        return (0);
    stack = malloc(sizeof(t_stack));
    if (!stack)
        exit(1);
    take_input(argc, argv, stack);
    if (!stack->a)
        return (free_all(stack, NULL), ft_putstr_fd("Error\n", 1), 1);
    check_duplicates(stack);
    stack->sorted = temp_order(stack);
    M = made_matrix(stack);
    print_matrix(M, stack->size_a);
    free_all(stack, M);
    return (0);
}
