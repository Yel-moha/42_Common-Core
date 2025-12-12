#include "push_swap.h"

void free_all(t_stack *stack)
{
    if (stack->a)
    {
        free(stack->a);
        stack->a = NULL;
    }
    if (stack->b)
    {
        free(stack->b);
        stack->b = NULL;
    }
    if (stack->sorted)
    {
        free(stack->sorted);
        stack->sorted = NULL;
    }
}

int main(int argc, char **argv)
{
    t_stack stack;

    if (argc < 2)
        return (0);
    take_input(argc, argv, &stack);
    cycle_sort(&stack);
    free_all(&stack);
    return (0);
}
