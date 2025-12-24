/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:36:52 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/01 17:12:06 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dest && !src)
		return (NULL);
	d = (char *)dest;
	s = (const char *)src;
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
	{
		d = (char *)dest + n;
		s = (const char *)src + n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}
/* #include <stdio.h>
#include <string.h>

int main()
{
	char str1[] = "Hello World";
	char str2[20];
	char str3[20];
	
	// Test case 1: Basic copy
	ft_memmove(str2, str1, strlen(str1) + 1);
	memmove(str3, str1, strlen(str1) + 1);
	printf("Test 1: ft_memmove: %s\n", str2);
	printf("Test 1: memmove: %s\n", str3);
	
	// Test case 2: Overlapping memory (forward)
	char overlap1[] = "Hello World";
	char overlap2[] = "Hello World";
	ft_memmove(overlap1 + 6, overlap1, 5);
	memmove(overlap2 + 6, overlap2, 5);
	printf("Test 2: ft_memmove: %s\n", overlap1);
	printf("Test 2: memmove: %s\n", overlap2);
	
	// Test case 3: Overlapping memory (backward)
	char overlap3[] = "Hello World";
	char overlap4[] = "Hello World";
	ft_memmove(overlap3, overlap3 + 6, 5);
	memmove(overlap4, overlap4 + 6, 5);
	printf("Test 3: ft_memmove: %s\n", overlap3);
	printf("Test 3: memmove: %s\n", overlap4);
	
	// Test case 4: Zero bytes
	ft_memmove(str2, str1, 0);
	memmove(str3, str1, 0);
	printf("Test 4: ft_memmove: %s\n", str2);
	printf("Test 4: memmove: %s\n", str3);
	
	// Test case 5: One byte
	ft_memmove(str2, str1, 1);
	memmove(str3, str1, 1);
	printf("Test 5: ft_memmove: %.1s\n", str2);
	printf("Test 5: memmove: %.1s\n", str3);
	
	// Test case 6: Large data
	char large1[1000];
	char large2[1000];
	char large3[1000];
	memset(large1, 'A', 999);
	large1[999] = '\0';
	ft_memmove(large2, large1, 1000);
	memmove(large3, large1, 1000);
	printf("Test 6: ft_memmove: %.10s...\n", large2);
	printf("Test 6: memmove: %.10s...\n", large3);
	
	// Test case 7: NULL source
	char null_test1[10];
	char null_test2[10];
	ft_memmove(null_test1, NULL, 0);
	//memmove(null_test2, NULL, 0);
	printf("Test 7: ft_memmove completed\n");
	printf("Test 7: memmove completed\n");
	
	// Test case 8: Special characters
	char special1[] = "!@#$%^&*()";
	char special2[20];
	char special3[20];
	ft_memmove(special2, special1, strlen(special1) + 1);
	memmove(special3, special1, strlen(special1) + 1);
	printf("Test 8: ft_memmove: %s\n", special2);
	printf("Test 8: memmove: %s\n", special3);
	
	// Continue with more test cases...
	// Test cases 9-50 would follow similar patterns testing different:
	// - String lengths
	// - Character types
	// - Memory alignments
	// - Edge cases
	// - Boundary conditions
	
	return 0;
} */