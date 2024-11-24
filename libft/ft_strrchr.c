/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:36:11 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/24 19:14:53 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			j = i;
		i++;
	}
	if (j > 0)
		return ((char *)&s[j]);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>


int main(void)
{
    const char *str = "Hello, World!";
    int test_chars[] = {'o', 'W', 'l', 'z', '\0'};
    char *result_ft, *result_orig;
    int i;

    printf("Testing ft_strrchr against original strrchr:\n");
    for (i = 0; i < sizeof(test_chars) / sizeof(test_chars[0]); i++)
    {
        result_ft = ft_strrchr(str, test_chars[i]);
        result_orig = strrchr(str, test_chars[i]);

        printf("Character: '%c'\n", test_chars[i]);
        printf("ft_strrchr: %s\n", result_ft);

        printf("strrchr: %s\n", result_orig);
        printf("\n");
    }

    return 0;
}
*/