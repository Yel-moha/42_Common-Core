#include "push_swap.h"

static void send_chunk_to_b(t_stack *stack, int chunk_max)
{
    int count;

    count = 0;
    while (count < stack->size_a)
    {
        if (stack->a[0] <= chunk_max)
        {
            pb(stack);
            count++;
        }
        else
            ra(stack);
    }
}

void sort_chunk(t_stack *stack, int chunks)
{
    int chunk_size;
    int i;
    int chunk_max;

    chunk_size = stack->size / chunks;
    i = 0;
    while (i < chunks)
    {
        chunk_max = stack->sorted[(i + 1) * chunk_size - 1];
        send_chunk_to_b(stack, chunk_max);
        i++;
    }
}

static int find_max_pos(int *stack_b, int size_b)
{
    int i;
    int max;
    int pos;

    i = 0;
    max = stack_b[0];
    pos = 0;
    while (++i < size_b)
    {
        if (stack_b[i] > max)
        {
            max = stack_b[i];
            pos = i;
        }
    }
    return (pos);
}

void move_back_to_a(t_stack *stack)
{
    int max_pos;

    while (stack->size_b > 0)
    {
        max_pos = find_max_pos(stack->b, stack->size_b);
        if (max_pos <= stack->size_b / 2)
            while (max_pos-- > 0)
                rb(stack);
        else
            while (max_pos++ < stack->size_b)
                rrb(stack);
        pa(stack);
    }
}

void chunk_sort(t_stack *stack)
{
    if (stack->size_a <= 100)
        sort_chunk(stack, 5);
    else
        sort_chunk(stack, 11);
    move_back_to_a(stack);
}
