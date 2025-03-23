#include "push_swap.h"

// Trova il numero di bit massimi necessari
static int max_bits(t_stack *stack)
{
    int max;
    int bits;

    max = stack->size_a - 1;
    bits = 0;
    while ((max >> bits) != 0)
        bits++;
    return (bits);
}

// Normalizza i valori in stack->a: ogni numero diventa il suo indice nell'ordinamento
void normalize_stack(t_stack *stack)
{
    int *temp;
    int i;
    int j;

    temp = malloc(sizeof(int) * stack->size_a);
    if (!temp)
        exit(1);
    i = 0;
    while (i < stack->size_a)
    {
        temp[i] = 0;
        j = 0;
        while (j < stack->size_a)
        {
            if (stack->a[j] < stack->a[i])
                temp[i]++;
            j++;
        }
        i++;
    }
    i = 0;
    while (i < stack->size_a)
    {
        stack->a[i] = temp[i];
        i++;
    }
    free(temp);
}

// Radix sort usando bitwise (solo stack a e b)
void radix_sort(t_stack *stack)
{
    int i;
    int j;
    int bits;
    int size;

    normalize_stack(stack);
    bits = max_bits(stack);
    i = 0;
    while (i < bits)
    {
        j = 0;
        size = stack->size_a;
        while (j < size)
        {
            if (((stack->a[0] >> i) & 1) == 0)
                pb(stack);
            else
                ra(stack);
            j++;
        }
        while (stack->size_b > 0)
            pa(stack);
        i++;
    }
    cycle_sort(stack);
    ft_printf("Radix sort: %d operazioni\n", stack->moves);
}
