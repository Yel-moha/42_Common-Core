/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:38:32 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/19 21:39:29 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = s;
	while (n--)
		*p++ = '\0';
}
/* 
#include <stdio.h>

int main()
{
    // Test case 1-10: Different size arrays with characters
    char str1[10] = "Hello";
    char str2[10] = "Hello";
    printf("Test 1: Original string: %s\n", str1);
    bzero(str1, 5);
    ft_bzero(str2, 5);
    printf("After bzero(5): %s\nAfter ft_bzero(5): %s\n\n", str1, str2);

    // Test case 11-20: Arrays with numbers
    int nums1[5] = {1, 2, 3, 4, 5};
    int nums2[5] = {1, 2, 3, 4, 5};
	printf("Test 2: Before: %d %d %d %d %d\n", 
	nums1[0], nums1[1], nums1[2], nums1[3], nums1[4]);
    bzero(nums1, sizeof(int) * 3);
    ft_bzero(nums2, sizeof(int) * 3);
    printf("After bzero(12): %d %d %d %d %d\n", 
	nums1[0], nums1[1], nums1[2], nums1[3], nums1[4]);
    printf("After ft_bzero(12): %d %d %d %d %d\n\n", 
	nums2[0], nums2[1], nums2[2], nums2[3], nums2[4]);

    // Test case 21-30: Zero bytes
    char str3[5] = "Test";
    char str4[5] = "Test";
    printf("Test 3: Original string: %s\n", str3);
    bzero(str3, 0);
    ft_bzero(str4, 0);
    printf("After bzero(0): %s\nAfter ft_bzero(0): %s\n\n", str3 + 1, str4);

    // Test case 31-40: Single byte
    char c1 = 'A';
    char c2 = 'A';
    printf("Test 4: Original char: %c\n", c1);
    bzero(&c1, 1);
    ft_bzero(&c2, 1);
    printf("After bzero(1): %c\nAfter ft_bzero(1): %c\n\n", c1, c2);

    // Test case 41-50: Large array
    char large1[100];
    char large2[100];
    memset(large1, 'X', 100);
    memset(large2, 'X', 100);
    large1[99] = '\0';
    large2[99] = '\0';
    printf("Test 5: Original large string: %.10s...\n", large1);
    bzero(large1, 50);
    ft_bzero(large2, 50);
    printf("After bzero(50): %.10s...\nAfter 
	ft_bzero(50): %.10s...\n\n", large1, large2);

    return 0;
}

 */