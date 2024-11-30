/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:58:42 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/30 17:34:57 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ends(const char *str, char c, int n);
static int	begins(const char *str, char c, int n);
static int	count_words(const char *str, char c);
static char	**free_split(char **split);

char	**ft_split(char const *s, char c)
{
	char	**ssp;
	char	*str;
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	str = ft_strtrim(s, &c);
	ssp = ft_calloc(count_words(str, c) + 1, sizeof(char *));
	if (ssp == NULL)
		return (ssp);
	while (str[i] != '\0' && ssp != NULL)
	{
		i = begins(str, c, i);
		start = i;
		i = ends(str, c, i);
		ssp[j] = ft_substr(str, start, i - start);
		if (ssp[j] == NULL)
			return (free_split(ssp));
		j++;
	}
	return (ssp);
}

static int	begins(const char *str, char c, int n)
{
	while (str[n] != '\0' && str[n] == c)
		n++;
	return (n);
}

static int	ends(const char *str, char c, int n)
{
	while (str[n] != '\0' && str[n] != c)
		n++;
	return (n);
}

static int	count_words(const char *str, char c)
{
	int		count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
		{
			count++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
	}
	return (count);
}

static char	**free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (split);
}


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
 