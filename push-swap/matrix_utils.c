#include "push_swap.h"


static void write_matrix_ones(int **M, int *sorted, int *a, int size)
{
    int i;
    int j;
    int found;

    i = 0;
    while (i < size)
    {
        found = 0;
        j = 0;
        while (j < size)
        {
            if (a[i] == sorted[j])
            {
                M[i][j] = 1;
                found = 1;
            }
            j++;
        }
        if (!found)
            M[i][i] = 1;
        i++;
    }
}


static int **create_matrix(int **M, t_stack *stack)
{
    int i;

    i = 0;
    while (i < stack->size_a)
    {
        ft_bzero(M[i], sizeof(int) * stack->size_a);
        i++;
    }
    write_matrix_ones(M, stack->sorted, stack->a, stack->size_a);
    return (M);
}

int **made_matrix(t_stack *stack)
{
    int **M;
    int k;

    M = malloc(stack->size_a * sizeof(int *));
    if (!M)
        exit(1);
    k = 0;
    while (k < stack->size_a)
    {
        M[k] = malloc(stack->size_a * sizeof(int));
        if (!M[k])
            exit(1);
        ft_bzero(M[k], stack->size_a * sizeof(int));
        k++;
    }
    create_matrix(M, stack);
    return (M);
}

void print_matrix(int **M, int size)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            ft_printf("%d ", M[i][j]);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}
