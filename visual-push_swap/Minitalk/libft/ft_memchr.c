/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:15:49 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/24 19:23:36 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;
	char	ch;

	i = 0;
	str = (char *)s;
	ch = (char)c;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *)&str[i]);
		i++;
	}
	return (0);
}
/* 

#include <stdio.h>
#include <string.h>

int main(void)
{
    const char *s = "Hello, Worllojosuibuid!";
    char c = 'd';
    size_t n = 13;

    void *result1 = ft_memchr(s, c, n);
    void *result2 = memchr(s, c, n);

    if (result1 == result2)
        printf("Both functions returned the same pointer.\n");
    else
        printf("Functions returned different pointers.\n");

    if (result1)
        printf("ft_memchr found '%c' at position: 
		%ld\n", c, (char *)result1 - s);
    else
        printf("ft_memchr did not find '%c'.\n", c);

    if (result2)
        printf("memchr found '%c' at position: %ld\n", c, (char *)result2 - s);
    else
        printf("memchr did not find '%c'.\n", c);

    return 0;
}
 */