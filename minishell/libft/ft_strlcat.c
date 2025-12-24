/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:16:21 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/24 20:55:12 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = ft_strlen(dst);
	k = j;
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	while (src[i] != '\0' && j + 1 < size)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (ft_strlen(src) + k);
}
/* 
#include <stdio.h>
#include <bsd/string.h>


int main(void)
{
    char dst1[20] = "Hellooooo, ";
    char src1[] = "worhhhhhhhhhhhhhhhhhhhhhhhhhhhhld";
    char dst2[20] = "Hellooooo, ";
    char src2[] = "worhhhhhhhhhhhhhhhhhhhhhhhhhhhhld";
    
    size_t result1 = ft_strlcat(dst1, src1, sizeof(dst1));
    size_t result2 = strlcat(dst2, src2, sizeof(dst2));
    
    printf("Custom ft_strlcat: %s (result: %zu)\n", dst1, result1);
    printf("Original strlcat: %s (result: %zu)\n", dst2, result2);
    
    return 0;
}

 */