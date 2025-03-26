#include "push_swap.h"

void check_duplicates(t_stack *stack)
{
    int i;
    int j;

    i = 0;
    while (i < stack->size_a)
    {
        j = i + 1;
        while (j < stack->size_a)
        {
            if (stack->a[i] == stack->a[j])
            {
                ft_putstr_fd("Error\n", 1);
                exit(1);
            }
            j++;
        }
        i++;
    }
}

int order_them(int *array, int size, int j, int i)
{
    int temp;

    while (j < size)
    {
        if (array[j] > array[i])
        {
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
        j++;
    }
    return (array[i]);
}

int *temp_order(t_stack *stack)
{
    int *temp;
    int i;
    int j;
    int size;

    size = stack->size_a;
    temp = malloc(sizeof(int) * size);
    if (!temp)
        exit(1);
    i = -1;
    while (++i < size)
        temp[i] = stack->a[i];
    i = -1;
    while (++i < size)
    {
        j = i + 1;
        temp[i] = order_them(temp, size, j, i);
    }
    return (temp);
}

int is_sorted(t_stack *stack)
{
    int i;

    i = 0;
    while (i < stack->size_a - 1)
    {
        if (stack->a[i] > stack->a[i + 1])
            return (0); // ❌ Non ordinato
        i++;
    }
    return (1); // ✅ Ordinato
}
