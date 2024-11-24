/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:50:10 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/23 18:40:39 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	j;
	size_t	i;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/* #include <stdio.h>
#include <string.h>

int main()
{
    char *big = "Hello, world!";
    char *little = "";
    size_t len = 15;
	char *result = ft_strnstr(big, little, len);
	if (result != NULL)
	{
		printf("Substring found: %s\n", result);
	}
	else
	{
		printf("Substring not found.\n");
	}
	return 0;
} */