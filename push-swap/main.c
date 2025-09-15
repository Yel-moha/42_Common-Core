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

// Gestisce i casi in base alla dimensione dello stack
static void sort_stack(t_stack *stack)
{
   // if (stack->size_a <= 3)
     //   sort_three(stack);
    if (stack->size_a <= 20)
        cycle_sort(stack);
    else
        radix_sort(stack);
}

int main(int argc, char **argv)
{
    t_stack stack;

    if (argc < 2)
        return (0);
    take_input(argc, argv, &stack);
    sort_stack(&stack);
    free_all(&stack);
    return (0);
}
