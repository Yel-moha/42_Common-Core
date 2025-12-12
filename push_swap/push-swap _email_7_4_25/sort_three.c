#include "push_swap.h"

void	sort_three(t_stack *stack)
{
	if (!stack || stack->size_a != 3)
		return ;
	if (stack->a[0] > stack->a[1] && stack->a[1] < stack->a[2]
		&& stack->a[0] < stack->a[2])
		sa(stack);
	else if (stack->a[0] > stack->a[1] && stack->a[1] > stack->a[2])
	{
		sa(stack);
		rra(stack);
	}
	else if (stack->a[0] > stack->a[1] && stack->a[1] < stack->a[2])
		ra(stack);
	else if (stack->a[0] < stack->a[1] && stack->a[1] > stack->a[2]
		&& stack->a[0] < stack->a[2])
	{
		sa(stack);
		ra(stack);
	}
	else if (stack->a[0] < stack->a[1] && stack->a[1] > stack->a[2])
		rra(stack);
}
