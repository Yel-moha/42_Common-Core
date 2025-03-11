#include <stdlib.h>
#include <stdio.h>

typedef struct s_stack
{
    int *a;
    int *b;
    int size_a;
    int size_b;
} t_stack;

int *inputs_array(int argc, char **argv)
{
    int *array;
    int i;

    array = (int *)malloc(sizeof(int) * (argc - 1));
    if (array == NULL)
        return (NULL);

    i = argc - 1;
    while (i > 0)
    {
        if (!ft_isdigit(ft_atoi(argv[i])))
        {
            free(array);
            return (NULL);
        }
        array[argc - 1 - i] = ft_atoi(argv[i]);
        i--;    
    }
    return (array);
}

void    take_input(int argc, char **argv, t_stack *stack)
{
    stack->size_a = argc - 1;
    stack->size_b = 0;
    stack->a = inputs_array(argc, argv);
    stack->b = (int *)malloc(sizeof(int) * (argc - 1));
    if (stack->a == NULL || stack->b == NULL)
    {
        free(stack->a);
        free(stack->b);
        exit(1);
    }
    printf("size_a: %d\n", stack->size_a);
    printf("size_b: %d\n", stack->size_b);
    printf("a: %p\n", stack->a);
    printf("b: %p\n", stack->b);
}
