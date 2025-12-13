/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_min_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:30:36 by yel-moha          #+#    #+#             */
/*   Updated: 2025/12/13 17:30:38 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
