/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:32:38 by yel-moha          #+#    #+#             */
/*   Updated: 2025/12/13 17:32:39 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_closest_bigger(t_stack *stack, int value)
{
	int	i;
	int	pos;
	int	closest;

	i = 0;
	pos = -1;
	closest = INT_MAX;
	while (i < stack->size_a)
	{
		if (stack->a[i] > value && stack->a[i] < closest)
		{
			closest = stack->a[i];
			pos = i;
		}
		i++;
	}
	return (pos);
}

void	fill_normalized(int *temp, int *a, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		temp[i] = 0;
		j = 0;
		while (j < size)
		{
			if (a[j] < a[i])
				temp[i]++;
			j++;
		}
		i++;
	}
}

int	find_min_pos_index(t_stack *stack)
{
	int	i;
	int	min;
	int	pos;

	i = 0;
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

void	rotate_count(t_stack *stack, int count,
	void (*rotate_func)(t_stack *))
{
	while (count-- > 0)
		rotate_func(stack);
}
