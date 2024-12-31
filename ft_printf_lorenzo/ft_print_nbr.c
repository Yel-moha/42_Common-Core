/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:04:38 by lbarzant          #+#    #+#             */
/*   Updated: 2024/12/03 22:52:21 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nbr(int n)
{
	char	d[10];
	int		i;
	int		count;

	count = 0;
	if (n == -2147483648)
		return (print_string("-2147483648"));
	if (n < 0)
	{
		n = -n;
		count += print_char('-');
	}
	i = 0;
	while (n >= 10)
	{
		d[i++] = (n % 10) + '0';
		n /= 10;
	}
	d[i] = (n % 10) + '0';
	while (i >= 0)
		count += print_char(d[i--]);
	return (count);
}

int	print_unbr(unsigned int n)
{
	char	d[10];
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (n >= 10)
	{
		d[i++] = (n % 10) + '0';
		n /= 10;
	}
	d[i] = (n % 10) + '0';
	while (i >= 0)
		count += print_char(d[i--]);
	return (count);
}
