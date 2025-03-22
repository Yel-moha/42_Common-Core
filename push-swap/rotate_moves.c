#include "push_swap.h"

static void rotate(t_stack *stack, int *stack_a_and_b)
{
    int tmp;
    int i;

    if (stack->size_a < 2)
        return ;
    tmp = stack_a_and_b[0];
    i = 0;
    while (++i < stack->size_a)
        stack_a_and_b[i - 1] = stack_a_and_b[i];
    stack_a_and_b[stack->size_a - 1] = tmp;
}
void ra(t_stack *stack)
{
    rotate(stack, stack->a);
    stack->moves++;
    ft_printf("ra\n");
}

void rb(t_stack *stack)
{
    rotate(stack, stack->b);
    stack->moves++;
    ft_printf("rb\n");
}

void rr(t_stack *stack)
{
    ra(stack);
    rb(stack);
    stack->moves++;
    ft_printf("rr\n");
}

static void reverse_rotate(t_stack *stack, int *stack_a_and_b)
{
    int tmp;
    int i;

    if (stack->size_a < 2)
        return ;
    tmp = stack_a_and_b[stack->size_a - 1];
    i = stack->size_a;
    while (--i > 0)
        stack_a_and_b[i] = stack_a_and_b[i - 1];
    stack_a_and_b[0] = tmp;
}

void rra(t_stack *stack)
{
    reverse_rotate(stack, stack->a);
    stack->moves++;
    ft_printf("rra\n");
}

void rrb(t_stack *stack)
{
    reverse_rotate(stack, stack->b);
    stack->moves++;
    ft_printf("rrb\n");
}
void rrr(t_stack *stack)
{
    rra(stack);
    rrb(stack);
    stack->moves++;
    ft_printf("rrr\n");
}

