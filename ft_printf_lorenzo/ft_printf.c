/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarzant <lbarzant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:46:07 by lbarzant          #+#    #+#             */
/*   Updated: 2024/11/30 17:15:21 by lbarzant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	print_null(int mode)
{
	char	*s;
	int		i;

	if (mode == 1)
		s = "(null)";
	else
		s = "(nil)";
	i = -1;
	while (s[++i])
		print_char(s[i]);
	return (i);
}

int	print_string(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (print_null(1));
	while (s[++i])
		print_char(s[i]);
	return (i);
}

static int	format(va_list args, const char regex)
{
	if (regex == 'c')
		return (print_char(va_arg(args, int)));
	else if (regex == 's')
		return (print_string(va_arg(args, char *)));
	else if (regex == 'p')
		return (print_void(va_arg(args, void *)));
	else if (regex == 'd' || regex == 'i')
		return (print_nbr(va_arg(args, int)));
	else if (regex == 'u')
		return (print_unbr(va_arg(args, unsigned int)));
	else if (regex == 'x' || regex == 'X')
		return (print_uint_ex(va_arg(args, unsigned int), regex));
	else if (regex == '%')
		return (print_char('%'));
	return (0);
}

int	ft_printf(const char *regex, ...)
{
	va_list	args;
	int		i;
	int		printed;

	i = -1;
	printed = 0;
	va_start(args, regex);
	while (regex[++i])
	{
		if (regex[i] == '%')
			printed += format(args, regex[++i]);
		else
			printed += print_char(regex[i]);
	}
	va_end(args);
	return (printed);
}
