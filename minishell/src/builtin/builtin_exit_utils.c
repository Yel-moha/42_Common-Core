/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:22:16 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:22:17 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_sign(const char **s)
{
	int	neg;

	neg = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			neg = -1;
		(*s)++;
	}
	return (neg);
}

int	add_digit(long *val, int digit, int neg)
{
	long	max;
	long	min;

	max = 9223372036854775807L;
	min = -9223372036854775807L - 1;
	if ((neg == 1 && *val > (max - digit) / 10))
		return (0);
	if ((neg == -1 && -(*val) < (min + digit) / 10))
		return (0);
	*val = *val * 10 + digit;
	return (1);
}

int	ft_atol_safe(const char *s, long *res)
{
	long	val;
	int		neg;
	int		valid;

	val = 0;
	neg = get_sign(&s);
	valid = 1;
	while (*s && valid)
	{
		if (!ft_isdigit(*s))
			valid = 0;
		else
			valid = add_digit(&val, (*s - '0'), neg);
		s++;
	}
	if (!valid)
		return (0);
	*res = val * neg;
	return (1);
}
