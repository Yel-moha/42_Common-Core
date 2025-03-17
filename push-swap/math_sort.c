#include "push_swap.h"

static int next_index(int **M, int size, int current)
{
    int j;

    j = 0;
    while (j < size)
    {
        if (M[current][j])
            return (j);
        j++;
    }
    return (-1);
}

static int get_cycle(int **M, int size, int start, int *cycle)
{
    int len;
    int i;

    len = 0;
    i = start;
    while (1)
    {
        cycle[len++] = i;
        i = next_index(M, size, i);
        if (i == -1 || i == start)
            break ;
    }
    return (len);
}

static void execute_cycle_moves(t_stack *stack, int len)
{
    int i;

    i = 0;
    while (i < len - 1)
    {
        pb(stack);
        ra(stack);
        i++;
    }
    pb(stack);
    i = 0;
    while (i < len)
    {
        pa(stack);
        i++;
    }
}

static void find_and_execute_cycles(t_stack *stack, int **M, int size)
{
    int visited[size];
    int cycle[size];
    int i;
    int len;

    i = 0;
    while (i < size)
        visited[i++] = 0;
    i = 0;
    while (i < size)
    {
        if (!visited[i])
        {
            len = get_cycle(M, size, i, cycle);
            if (len > 1)
                execute_cycle_moves(stack, len);
            int k = 0;
            while (k < len)
                visited[cycle[k++]] = 1;
        }
        i++;
    }
}

void sort_from_cycles(t_stack *stack, int **M)
{
    find_and_execute_cycles(stack, M, stack->size_a);
}
