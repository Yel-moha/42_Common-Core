/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:56:18 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/01 17:39:26 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = ((str[i] - 48) + (num * 10));
		i++;
	}
	return (num * sign);
}
/* 
#include <stdio.h>


int main(void)
{
	const char *tests[20] = {
		"123", "-123", "+123", "   123", "0", 
		"999999", "   -999999", "   +999999", 
		"abc123", "123abc", "   +abc", "   -abc", 
		"   +0", "   -0", "   +1", "   -1", 
		"   +2147483647", "   -2147483648", 
		"2147483648", "-2147483649", "++++---12456h64"
	};
	int i;
	for (i = 0; i < 20; i++)
	{
		int my_res = ft_atoi(tests[i]);
		int original_res = atoi(tests[i]);
		printf("Test %d: Input: '%s' | My atoi: %d | Original atoi: %d\n", 
			i + 1, tests[i], my_res, original_res);
	}
	return (0);
}
 */