#include "push_swap.h"

int check_input(char *argv)
{
    size_t j;

    j = 0;
    if (argv[0] == '+' || argv[0] == '-')
        j = 1;
    while (argv[j])
    {
        if (!ft_isdigit(argv[j]))
        {
            ft_putstr_fd("Error\n", 1);
            return (0);
        }
        j++;
    }
    return (1);
}

int *inputs_array(int argc, char **argv)
{
    int *array;
    int i;
    int idx;

    array = malloc(sizeof(int) * (argc - 1));
    if (!array)
        return (NULL);

    i = argc - 1;
    idx = 0;
    while (i > 0)
    {
        if (!check_input(argv[i]))
        {
            free(array);
            return (NULL);
        }
        array[idx++] = ft_atoi(argv[i]);
        i--;
    }
    return (array);
}

/* void init_stack(t_stack *stack, int argc)
{
    stack->a = malloc(sizeof(int) * (argc - 1));
    stack->b = malloc(sizeof(int) * (argc - 1));
    if (!stack->a || !stack->b)
    {
        free(stack->a);
        free(stack->b);
        exit(1);
    }
    stack->size_a = argc - 1;
    stack->size_b = 0;
} */

void take_input(int argc, char **argv, t_stack *stack)
{
    init_stack(stack, argc);
    stack->a = inputs_array(argc, argv);  // ← malloc avviene dentro
    stack->b = malloc(sizeof(int) * (argc - 1));
    stack->sorted = malloc(sizeof(int) * (argc - 1));
    if (!stack->a || !stack->b || !stack->sorted)
    {
        free(stack->a);
        free(stack->b);
        free(stack->sorted);
        exit(1);
    }
    ft_memcpy(stack->sorted, stack->a, sizeof(int) * (argc - 1)); // copia ordinabile
    check_duplicates(stack);
}


void init_stack(t_stack *stack, int argc)
{
    stack->size_a = argc - 1;
    stack->size_b = 0;
    stack->moves = 0;
    stack->a = NULL;
    stack->b = NULL;
}
