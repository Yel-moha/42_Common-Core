/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:32:54 by yel-moha          #+#    #+#             */
/*   Updated: 2025/12/13 17:32:55 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	normalize_stack(t_stack *stack)
{
	int	*temp;
	int	i;

	temp = malloc(sizeof(int) * stack->size_a);
	if (!temp)
		exit(1);
	fill_normalized(temp, stack->a, stack->size_a);
	i = 0;
	while (i < stack->size_a)
	{
		stack->a[i] = temp[i];
		i++;
	}
	free(temp);
}

int	target_position(t_stack *stack, int value)
{
	int	pos;

	pos = find_closest_bigger(stack, value);
	if (pos != -1)
		return (pos);
	return (find_min_pos_index(stack));
}

int	get_cost(int size, int pos)
{
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

int	find_best_index(t_stack *stack)
{
	int	i;
	int	best;
	int	cost;
	int	pos_a;

	i = 0;
	best = 0;
	cost = INT_MAX;
	while (i < stack->size_b)
	{
		pos_a = target_position(stack, stack->b[i]);
		if (get_cost(stack->size_a, pos_a) + get_cost(stack->size_b, i) < cost)
		{
			cost = get_cost(stack->size_a, pos_a) + get_cost(stack->size_b, i);
			best = i;
		}
		i++;
	}
	return (best);
}

void	bring_to_top(t_stack *stack, int pos, char id)
{
	int		count;
	int		size;
	void	(*rotate_func)(t_stack *);
	void	(*rev_func)(t_stack *);

	if (id == 'a')
	{
		size = stack->size_a;
		rotate_func = ra;
		rev_func = rra;
	}
	else
	{
		size = stack->size_b;
		rotate_func = rb;
		rev_func = rrb;
	}
	if (pos <= size / 2)
		rotate_count(stack, pos, rotate_func);
	else
	{
		count = size - pos;
		rotate_count(stack, count, rev_func);
	}
}
