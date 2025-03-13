#include <stdlib.h>
#include <stdio.h>
#include "push_swap.h"

int *inputs_array(int argc, char **argv)
{
    int *array;
    int i;
    size_t j;

    array = (int *)malloc(sizeof(int) * (argc - 1));
    if (array == NULL)
        return (NULL);
    i = argc;
    while (--i > 0)
    {
        j = 0;
        if(!check_input(argv[i], j, array))
            return (NULL);
        array[argc - 1 - i] = ft_atoi(argv[i]);
        printf("array[%d]: %d\n", argc - 1 - i, array[argc - 1 - i]);
    }
    return (array);
}

int check_input(char *argv, size_t j, int *array)
{
    if (argv[0] == '+' || argv[0] == '-')
        j = 1;
    while (j < ft_strlen(argv))
    {
        if (argv[j] < '0' || argv[j] > '9')
        {
            free(array);
            return (0);
        }
        j++;
    }
    return (1);
}

void    take_input(int argc, char **argv, t_stack *stack)
{
    stack->size_a = argc - 1;
    stack->size_b = 0;
    stack->a = inputs_array(argc, argv);
    //printf("a: %p\n", stack->a);
    stack->b = (int *)malloc(sizeof(int) * (argc - 1));
    if (stack->a == NULL || stack->b == NULL)
    {
        free(stack->a);
        free(stack->b);
        exit(1);
    }
    printf("size_a: %d\n", stack->size_a);
    printf("size_b: %d\n", stack->size_b);
   // printf("a: %p\n", stack->a);
   // printf("b: %p\n", stack->b);
}

void    check_duplicates(t_stack *stack)
{
    int i;
    int j;
    int size;
   
    i = -1;
    size = stack->size_a;
    i = -1;
    while (++i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (stack->a[i] == stack->a[j])
            {
                ft_putstr_fd("Error\n", 1);
                exit(1);
            }
            j++;
        }
    }
}

int *temp_order(t_stack *stack)
{
    int *temp;
    int i;
    int j;
    int size;

    size = stack->size_a;
    temp = (int *)malloc(sizeof(int) * size);
    if (temp == NULL)
        return (NULL);
    i = -1;
    while (++i < size)
    {
        temp[i] = stack->a[i];
    }
    i = -1;
    while (++i < size)
    {
        j = i + 1;
        temp[i] = order_them(temp, size, j, i);
        printf("temp[%d]: %d\n", i, temp[i]);
    }
    return (temp);
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
