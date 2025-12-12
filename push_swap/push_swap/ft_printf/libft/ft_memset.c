/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:28:17 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/19 21:39:58 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = (unsigned char)c;
	return (s);
}
/* 
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[50] = "Hello World";
    char str2[50] = "Hello World";
    
    printf("Before ft_memset: %s\n", str1);
    printf("Before memset: %s\n", str2);
    
    ft_memset(str1, 'a', 22);
    memset(str2, 'a', 22);
    
    printf("After ft_memset: %s\n", str1);
    printf("After memset: %s\n", str2);
    
    // Test with different size and character
    char str3[50] = "Testing another case";
    char str4[50] = "Testing another case";
    
    printf("\nBefore ft_memset: %s\n", str3);
    printf("Before memset: %s\n", str4);
    
    ft_memset(str3, '#', 7);
    memset(str4, '#', 7);
    
    printf("After ft_memset: %s\n", str3);
    printf("After memset: %s\n", str4);
    
    return (0);
} */