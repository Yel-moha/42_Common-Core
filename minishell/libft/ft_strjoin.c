/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:20:07 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/27 23:17:01 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	i = -1;
	j = -1;
	join = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!join)
		return (NULL);
	while (s1[++i])
	{
		join[i] = s1[i];
	}
	while (s2[++j])
	{
		join[j + i] = s2[j];
	}
	return (join);
}
/* 
 
#include <stdio.h>
#include "libft.h"

int main(void)
{
    char *result;

    // Test 1: Concatenazione di due stringhe normali
    char s1[] = "Hello, ";
    char s2[] = "World!";
    result = ft_strjoin(s1, s2);
    printf("Test 1: '%s' + '%s' = '%s'\n", s1, s2, result);
    free(result);

    // Test 2: Una stringa vuota
    char s3[] = "";
    char s4[] = "Test";
    result = ft_strjoin(s3, s4);
    printf("Test 2: '%s' + '%s' = '%s'\n", s3, s4, result);
    free(result);

    // Test 3: Entrambe le stringhe vuote
    char s5[] = "";
    char s6[] = "";
    result = ft_strjoin(s5, s6);
    printf("Test 3: '%s' + '%s' = '%s'\n", s5, s6, result);
    free(result);

    // Test 4: Stringa lunga
    char s7[] = "This is a very long string, ";
    char s8[] = "and this is another long string.";
    result = ft_strjoin(s7, s8);
    printf("Test 4: '%s' + '%s' = '%s'\n", s7, s8, result);
    free(result);

    return 0;
}
 */