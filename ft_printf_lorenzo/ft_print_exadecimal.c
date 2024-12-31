/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_exadecimal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarzant <lbarzant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:17:06 by lbarzant          #+#    #+#             */
/*   Updated: 2024/11/30 17:14:13 by lbarzant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_void(void *s)
{
	unsigned long	address;
	char			*hex_digits;
	int				count;
	int				i;
	char			d[16];

	hex_digits = "0123456789abcdef";
	address = (unsigned long) s;
	if (address == 0)
		return (print_null(2));
	print_char('0');
	print_char('x');
	count = 2;
	i = 0;
	while (address > 0)
	{
		d[i++] = hex_digits[address % 16];
		address /= 16;
	}
	while (i > 0)
	{
		print_char(d[--i]);
		count++;
	}
	return (count);
}

int	print_uint_ex(unsigned int n, char mode)
{
	char	*hex_digits;
	char	d[8];
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (mode == 'x')
		hex_digits = "0123456789abcdef";
	else if (mode == 'X')
		hex_digits = "0123456789ABCDEF";
	if (n == 0)
		return (print_char('0'));
	while (n > 0)
	{
		d[i++] = hex_digits[n % 16];
		n /= 16;
	}
	while (i > 0)
		count += print_char(d[--i]);
	return (count);
}
