/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:33:53 by yel-moha          #+#    #+#             */
/*   Updated: 2025/12/13 17:33:55 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(int *stack_array, int size)
{
	int	tmp;
	int	i;

	if (size < 2)
		return ;
	tmp = stack_array[size - 1];
	i = size;
	while (--i > 0)
		stack_array[i] = stack_array[i - 1];
	stack_array[0] = tmp;
}

void	rra(t_stack *stack)
{
	reverse_rotate(stack->a, stack->size_a);
	stack->moves++;
	ft_printf("rra\n");
}

void	rrb(t_stack *stack)
{
	reverse_rotate(stack->b, stack->size_b);
	stack->moves++;
	ft_printf("rrb\n");
}

void	rrr(t_stack *stack)
{
	reverse_rotate(stack->a, stack->size_a);
	reverse_rotate(stack->b, stack->size_b);
	stack->moves++;
	ft_printf("rrr\n");
}
