/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:18:16 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/28 01:12:49 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	strdx(const char *set, const char *str);
static unsigned int	strsx(const char *set, const char *str);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*nstr;
	size_t	i;

	i = strsx(s1, set);
	nstr = ft_calloc((strdx(set, s1) - i) + 1, sizeof(char));
	if (!nstr)
		return (NULL);
	nstr = ft_substr(s1, i, (strdx(set, s1) - i));
	return (nstr);
}

static unsigned int	strsx(const char *set, const char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (set[j])
		{
			if (set[j] == str[i])
				i++;
			else
				j++;
			if (j == ft_strlen(set) - 1)
				return (i);
		}
	}
	return (i);
}

static unsigned int	strdx(const char *set, const char *str)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(str) - 1;
	while (str[i])
	{
		while (set[j])
		{
			if (set[j] == str[i])
				i--;
			else
				j++;
			if (j == ft_strlen(set) - 1)
				return (i);
		}
	}
	return (i);
}
#include "libft.h"

int main(void)
{
    char *result;

    // Test 1: Trim di caratteri presenti su entrambi i lati
    char s1[] = "!!Hello, World!!!";
    char set[] = "!!!!";
    result = ft_strtrim(s1, set);
    printf("Test 1: '%s' trimmed by '%s' -> '%s'     dx =  %d    sx =   %d\n", s1, set, result, strdx(set, s1), strsx(s1, set));
    free(result);

    // Test 2: Trim di spazi bianchi
    char s2[] = "   Hello, World   ";
    char set2[] = " ";
    result = ft_strtrim(s2, set2);
    printf("Test 2: '%s' trimmed by '%s' -> '%s'\n", s2, set2, result);
    free(result);

    // Test 3: Nessun carattere da rimuovere
    char s3[] = "Hello, World";
    char set3[] = "xyz";
    result = ft_strtrim(s3, set3);
    printf("Test 3: '%s' trimmed by '%s' -> '%s'\n", s3, set3, result);
    free(result);

    // Test 4: Stringa vuota
    char s4[] = "";
    char set4[] = " ";
    result = ft_strtrim(s4, set4);
    printf("Test 4: '%s' trimmed by '%s' -> '%s'\n", s4, set4, result);
    free(result);

    // Test 5: Trim di una stringa completamente rimossa
    char s5[] = "aaaaaa";
    char set5[] = "a";
    result = ft_strtrim(s5, set5);
    printf("Test 5: '%s' trimmed by '%s' -> '%s'\n", s5, set5, result);
    free(result);

    // Test 6: Stringa da trim e set uguali
    char s6[] = "abc";
    char set6[] = "abc";
    result = ft_strtrim(s6, set6);
    printf("Test 6: '%s' trimmed by '%s' -> '%s'\n", s6, set6, result);
    free(result);

    return 0;
}
