#include "push_swap.h"

int	find_min_pos(t_stack *stack)
{
	int	i;
	int	min;
	int	pos;

	if (!stack || stack->size_a <= 0)
		return (-1);
	i = 1;
	min = stack->a[0];
	pos = 0;
	while (i < stack->size_a)
	{
		if (stack->a[i] < min)
		{
			min = stack->a[i];
			pos = i;
		}
		i++;
	}
	return (pos);
}
