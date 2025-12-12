/* #include "push_swap.h"

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
    stack->moves++;
    ft_printf("sa\n");
}

void sb(t_stack *stack)
{
    swap(stack->b, stack->size_b);
    stack->moves++;
    ft_printf("sb\n");
}

void ss(t_stack *stack)
{
    swap(stack->a, stack->size_a);
    swap(stack->b, stack->size_b);
    stack->moves++;
    ft_printf("ss\n");
}
 */

 #include "push_swap.h"

static void	swap(int *stack, int size)
{
	int	temp;

	if (size < 2)
		return ;
	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}

void	sa(t_stack *stack)
{
	swap(stack->a, stack->size_a);
	stack->moves++;
	ft_printf("sa\n");
}

void	sb(t_stack *stack)
{
	swap(stack->b, stack->size_b);
	stack->moves++;
	ft_printf("sb\n");
}

void	ss(t_stack *stack)
{
	swap(stack->a, stack->size_a);
	swap(stack->b, stack->size_b);
	stack->moves++;
	ft_printf("ss\n");
}
