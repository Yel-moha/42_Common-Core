/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:42:01 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/01 17:08:42 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dest && !src)
		return (NULL);
	d = (char *)dest;
	s = (const char *) src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
/* 
#include <stdio.h>
#include <string.h>

int main()
{
    // Test case 1: Basic string copy
    char dest1[50] = "";
    char src1[] = "Hello, World!";
    printf("Test 1 - Original memcpy: %s\n", 
	(char *)memcpy(dest1, src1, strlen(src1) + 1));
    
    char dest1_ft[50] = "";
    printf("Test 1 - ft_memcpy: %s\n\n", 
	(char *)ft_memcpy(dest1_ft, src1, strlen(src1) + 1));

    // Test case 2: Copy with numbers
    int src2[] = {1, 2, 3, 4, 5};
    int dest2[5];
    memcpy(dest2, src2, sizeof(src2));
    printf("Test 2 - Original memcpy: ");
    for(int i = 0; i < 5; i++)
        printf("%d ", dest2[i]);
    printf("\n");

    int dest2_ft[5];
    ft_memcpy(dest2_ft, src2, sizeof(src2));
    printf("Test 2 - ft_memcpy: ");
    for(int i = 0; i < 5; i++)
        printf("%d ", dest2_ft[i]);
    printf("\n\n");

    // Test case 3: Empty string
    char dest3[10] = "Test";
    char src3[] = "";
    printf("Test 3 - Original memcpy: %s\n", (
	char *)memcpy(dest3, src3, 1));
    
    char dest3_ft[10] = "Test";
    printf("Test 3 - ft_memcpy: %s\n\n", (char 
	*)ft_memcpy(dest3_ft, src3, 1));

    // Test case 4: Single character
    char dest4[10];
    char src4 = 'X';
    memcpy(dest4, &src4, 1);
    printf("Test 4 - Original memcpy: %c\n", dest4[0]);

    char dest4_ft[10];
    ft_memcpy(dest4_ft, &src4, 1);
    printf("Test 4 - ft_memcpy: %c\n\n", dest4_ft[0]);

    // Test case 5: Float numbers
    float src5[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float dest5[5];
    memcpy(dest5, src5, sizeof(src5));
    printf("Test 5 - Original memcpy: ");
    for(int i = 0; i < 5; i++)
        printf("%.1f ", dest5[i]);
    printf("\n");

    float dest5_ft[5];
    ft_memcpy(dest5_ft, src5, sizeof(src5));
    printf("Test 5 - ft_memcpy: ");
    for(int i = 0; i < 5; i++)
        printf("%.1f ", dest5_ft[i]);
    printf("\n\n");

    // Test case 6: Overlapping memory (undefined behavior)
    char str6[] = "Hello, World!";
	
    printf("Test 6 - Original memcpy: %s\n", (char *)me
	mcpy(str6 + 1, str6, 5));
    
    char str6_ft[] = "Hello, World!";
    printf("Test 6 - ft_memcpy: %s\n\n", (char *)ft_mem
	cpy(str6_ft + 1, str6_ft, 5));

    // Test case 7: Zero bytes
    char dest7[] = "Test";
    char src7[] = "Hello";
    printf("Test 7 - Original memcpy: %s\n", (char *)me
	mcpy(dest7, src7, 0));
    
    char dest7_ft[] = "Test";
    printf("Test 7 - ft_memcpy: %s\n\n", (char *)ft_mem
	cpy(dest7_ft, src7, 0));

    // Test case 8: Large string
    char src8[1000];
    char dest8[1000];
    char dest8_ft[1000];
    memset(src8, 'A', 999);
    src8[999] = '\0';
    
    printf("Test 8 - Original memcpy: %.10s...\n", (char *)memc
	py(dest8, src8, 1000));
    printf("Test 8 - ft_memcpy: %.10s...\n\n", (char *)ft_mem
	cpy(dest8_ft, src8, 1000));

    // Test case 9: Special characters
    char src9[] = "!@#$%^&*()";
    char dest9[20];
    char dest9_ft[20];
    
    printf("Test 9 - Original memcpy: %s\n", (char *)memc
	py(dest9, src9, strlen(src9) + 1));
    printf("Test 9 - ft_memcpy: %s\n\n", (char *)ft_memc
	py(dest9_ft, src9, strlen(src9) + 1));

    // Test case 10: Unicode characters
    char src10[] = "Hello 世界";
    char dest10[20];
    char dest10_ft[20];
    
    printf("Test 10 - Original memcpy: %s\n", (char *)memcp
	y(dest10, src10, strlen(src10) + 1));
    printf("Test 10 - ft_memcpy: %s\n\n", (char *)ft_memc
	py(dest10_ft, src10, strlen(src10) + 1));

    return 0;
}
 */
