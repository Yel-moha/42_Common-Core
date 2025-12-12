#include "push_swap.h"

static void	rotate(int *stack_array, int size)
{
	int	tmp;
	int	i;

	if (size < 2)
		return ;
	tmp = stack_array[0];
	i = 0;
	while (++i < size)
		stack_array[i - 1] = stack_array[i];
	stack_array[size - 1] = tmp;
}

void	ra(t_stack *stack)
{
	rotate(stack->a, stack->size_a);
	stack->moves++;
	ft_printf("ra\n");
}

void	rb(t_stack *stack)
{
	rotate(stack->b, stack->size_b);
	stack->moves++;
	ft_printf("rb\n");
}

void	rr(t_stack *stack)
{
	rotate(stack->a, stack->size_a);
	rotate(stack->b, stack->size_b);
	stack->moves++;
	ft_printf("rr\n");
}
