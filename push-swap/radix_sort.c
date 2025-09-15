#include "push_swap.h"

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

// Calcola il numero massimo di bit
static int max_bits(t_stack *stack)
{
    int max;
    int bits;

    max = stack->size_a - 1;
    bits = 0;
    while (max > 0)
    {
        bits++;
        max >>= 1;
    }
    return (bits);
}

// Esegue un ciclo del radix_sort (una sola cifra binaria)
/* static void radix_pass(t_stack *stack, int bit)
{
    int j;
    int size;

    j = 0;
    size = stack->size_a;
    while (j < size)
    {
        if (((stack->a[0] >> bit) & 1) == 0)
            pb(stack);
        else
            ra(stack);
        j++;
    }
    while (stack->size_b > 0)
        pa(stack);
} */

void radix_sort(t_stack *stack)
{
    int bit;
    int count;
    int bits_max;
    int num;

    normalize_stack(stack);
    bits_max = max_bits(stack);
    bit = 0;
    while (bit < bits_max)
    {
        count = stack->size_a;
        while (count--)
        {
            num = stack->a[0];
            if (((num >> bit) & 1) == 1)
                ra(stack);
            else
                pb(stack);
        }
        while (stack->size_b)
            pa(stack);
        bit++;
    }
}
