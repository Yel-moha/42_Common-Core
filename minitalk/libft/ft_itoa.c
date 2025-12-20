/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:18:51 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/01 22:26:27 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len_number(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*negative_itoa(int n)
{
	char	*numst;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = len_number(n);
	numst = ft_calloc(len + 1, sizeof(char));
	if (!numst)
		return (NULL);
	numst[0] = '-';
	n = -n;
	while (n > 0)
	{
		numst[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (numst);
}

static char	*ito_zero(void)
{
	char	*numst;

	numst = ft_calloc(2, sizeof(char));
	if (!numst)
		return (NULL);
	numst[0] = '0';
	numst[1] = '\0';
	return (numst);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*numst;

	len = len_number(n);
	if (n == 0)
		return (ito_zero());
	if (n < 0)
		return (negative_itoa(n));
	numst = ft_calloc(len + 1, sizeof(char));
	if (!numst)
		return (NULL);
	while (n > 0)
	{
		numst[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (numst);
}
