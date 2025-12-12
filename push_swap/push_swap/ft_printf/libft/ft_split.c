/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:58:42 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/01 20:18:47 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}

static char	**if_aux(char const *s, char c, char **result)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			result[j] = ft_substr(s, start, i - start);
			if (!result[j])
				return (free_split(result));
			j++;
		}
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	result = if_aux(s, c, result);
	return (result);
}
/* 
int main(void)
{
    char *str = "      split       this for   me  !       ";
    char **result;
    int i;

    result = ft_split(str, ' '); // Usa lo spazio come delimitatore

    if (result != NULL)
    {
        i = 0;
        while (result[i] != NULL)
        {
            printf("Word %d: '%s'\n", i, result[i]);
            free(result[i]); // Libera ogni parola
            i++;
        }
        free(result); // Libera l'array di puntatori
    }
    else
    {
        printf("ft_split returned NULL.\n");
    }

    return 0;
}
 */