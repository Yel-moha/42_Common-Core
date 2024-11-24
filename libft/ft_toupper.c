/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:17:52 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/23 17:33:44 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/* 
#include <stdio.h>
#include <ctype.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

int	main(void)
{
	char test_chars[] = {'a', 'b', 'c', 'A', 'B', 'C', '1', '!', '\0'};
	int i = 0;

	while (test_chars[i])
	{
		printf("Original: %c, Custom toupper: %c, Standard toupper: %c\n",
			test_chars[i],
			toupper(test_chars[i]),
			toupper(test_chars[i]));
		i++;
	}
	return (0);
}
 */