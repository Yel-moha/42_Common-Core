/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:06:39 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/27 00:01:43 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*nstr;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	nstr = ft_calloc(len + 1, sizeof(char));
	if (nstr == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		nstr[i] = s[start + i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
/* 

void test_ft_substr(char *s, unsigned int start, size_t len)
{
    char *result;

    printf("Input string: \"%s\", start: %u, len: %zu\n", s, start, len);
    result = ft_substr(s, start, len);
    if (result != NULL)
        printf("ft_substr result: \"%s\"\n", result);
    else
        printf("ft_substr result: NULL\n");

    free(result);
}
void test_ft_substr_extended(void)
{
    // Test with special characters
    test_ft_substr("Hello\n\tWorld!", 5, 3);  // "\n\t"
    test_ft_substr("Hello\0World", 0, 10);    // "Hello"
    
    // Test with non-ASCII characters
    test_ft_substr("héllø wørld", 2, 4);      // "llø "
    
    // Test with very large len
    test_ft_substr("small", 0, SIZE_MAX);     // "small"
    
    // Test with multiple spaces
    test_ft_substr("   spaces   ", 3, 6);     // "spaces"
    
    // Test with single character
    test_ft_substr("X", 0, 1);                // "X"
    
    // Test with overlapping len
    test_ft_substr("12345", 2, 10);           // "345"
    
    // Test with exact string length
    test_ft_substr("test", 0, 4);             // "test"
    
    // Test with numbers and symbols
    test_ft_substr("123!@#$%^", 3, 4);        // "!@#$"
}

int main(void)
{
    // Original tests
    test_ft_substr("Hello, world!", 0, 5);
    test_ft_substr("Hello, world!", 7, 5);
    
    // New extended tests
    test_ft_substr_extended();
    
    return 0;
}
 */