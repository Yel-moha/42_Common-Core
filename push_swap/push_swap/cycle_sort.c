/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:29:37 by yel-moha          #+#    #+#             */
/*   Updated: 2025/12/13 17:29:40 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	smart_insert(t_stack *stack)
{
	int	best_b;
	int	pos_a;
	int	first;
	int	last;

	if (!stack || stack->size_b <= 0)
		return ;
	best_b = find_best_index(stack);
	pos_a = target_position(stack, stack->b[best_b]);
	bring_to_top(stack, best_b, 'b');
	bring_to_top(stack, pos_a, 'a');
	pa(stack);
	if (stack->size_a >= 2)
	{
		first = stack->a[0];
		last = stack->a[stack->size_a - 1];
		if (last + 1 == first || (last == stack->max && first == stack->min))
			ra(stack);
	}
}

static void	rotate_to_target(t_stack *stack, int pos)
{
	if (pos <= stack->size_a / 2)
		while (pos-- > 0)
			ra(stack);
	else
	{
		pos = stack->size_a - pos;
		while (pos-- > 0)
			rra(stack);
	}
}

void	print_stacks(t_stack *stack)
{
	int	i;

	i = 0;
	ft_printf("STACK A: ");
	while (i < stack->size_a)
	{
		ft_printf("%d ", stack->a[i]);
		i++;
	}
	ft_printf("\nSTACK B: ");
	i = 0;
	while (i < stack->size_b)
	{
		ft_printf("%d ", stack->b[i]);
		i++;
	}
	ft_printf("\n---\n");
}

void	cycle_sort(t_stack *stack)
{
	if (!stack)
		return ;
	normalize_stack(stack);
	if (is_sorted(stack))
		return ;
	while (stack->size_a > 3)
		pb(stack);
	if (stack->size_a == 3)
		sort_three(stack);
	while (stack->size_b > 0)
		smart_insert(stack);
	rotate_to_target(stack, find_min_pos(stack));
}
