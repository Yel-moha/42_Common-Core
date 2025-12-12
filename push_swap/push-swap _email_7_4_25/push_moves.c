#include "push_swap.h"

static void	push(int *src, int *dst, int *size_src, int *size_dst)
{
	int	i;

	if (*size_src == 0)
		return ;
	i = *size_dst;
	while (i > 0)
	{
		dst[i] = dst[i - 1];
		i--;
	}
	dst[0] = src[0];
	(*size_dst)++;
	i = 0;
	while (i < (*size_src - 1))
	{
		src[i] = src[i + 1];
		i++;
	}
	(*size_src)--;
}

void	pa(t_stack *stack)
{
	if (stack->size_b == 0)
		return ;
	push(stack->b, stack->a, &stack->size_b, &stack->size_a);
	ft_printf("pa\n");
	stack->moves++;
}

void	pb(t_stack *stack)
{
	if (stack->size_a == 0)
		return ;
	push(stack->a, stack->b, &stack->size_a, &stack->size_b);
	ft_printf("pb\n");
	stack->moves++;
}
