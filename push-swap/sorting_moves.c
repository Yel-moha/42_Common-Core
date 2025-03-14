#include "push_swap.h"

// swap primi 2 elementi dello stack
static void swap(int *stack, int size)
{
    int temp;

    if (size < 2)
        return ;
    temp = stack[0];
    stack[0] = stack[1];
    stack[1] = temp;
}

void sa(t_stack *stack)
{
    swap(stack->a, stack->size_a);
    ft_printf("sa\n");
}

void sb(t_stack *stack)
{
    swap(stack->b, stack->size_b);
}

void ss(t_stack *stack)
{
    sa(stack);
    sb(stack);
}

// push: sposta il primo elemento da stack src a stack dst
static void push(int *src, int *dst, int *size_src, int *size_dst)
{
    int i;

    if (*src == 0)
        return ;
    i = ++(*size_dst);
    while (--i > 0)
        dst[i] = dst[i - 1];
    dst[0] = src[0];
    i = 0;
    while (++i < *size_src)
        src[i - 1] = src[i];
    (*size_src)--;
}

void pa(t_stack *stack)
{
    push(stack->b, stack->a, &(stack->size_b), &(stack->size_a));
}

void pb(t_stack *stack)
{
    push(stack->a, stack->b, &(stack->size_a), &(stack->size_b));
}

// rotate: primo elemento diventa ultimo
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
}

void rb(t_stack *stack)
{
    rotate(stack->b, stack->size_b);
}

void rr(t_stack *stack)
{
    ra(stack);
    rb(stack);
}

// reverse rotate: ultimo elemento diventa primo
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
}

void rrb(t_stack *stack)
{
    reverse_rotate(stack->b, stack->size_b);
}

void rrr(t_stack *stack)
{
    rra(stack);
    rrb(stack);
}
