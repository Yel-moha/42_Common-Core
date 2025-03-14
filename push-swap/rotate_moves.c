#include "push_swap.h"

static void rotate(int *stack, int size)
{
    int tmp;
    int i;

    if (size < 2)
        return ;
    tmp = stack[0];
    i = 0;
    while (++i < size)
        stack[i - 1] = stack[i];
    stack[size - 1] = tmp;
}

void ra(t_stack *stack)
{
    rotate(stack->a, stack->size_a);
    ft_printf("ra\n");
}

void rb(t_stack *stack)
{
    rotate(stack->b, stack->size_b);
    ft_printf("rb\n");
}

static void reverse_rotate(int *stack, int size)
{
    int tmp;
    int i;

    if (size < 2)
        return ;
    tmp = stack[size - 1];
    i = size;
    while (--i > 0)
        stack[i] = stack[i - 1];
    stack[0] = tmp;
}

void rra(t_stack *stack)
{
    reverse_rotate(stack->a, stack->size_a);
    ft_printf("rra\n");
}

void rrb(t_stack *stack)
{
    reverse_rotate(stack->b, stack->size_b);
    ft_printf("rrb\n");
}
void rrr(t_stack *stack)
{
    rra(stack);
    rrb(stack);
    ft_printf("rrr\n");
}

