/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:58:42 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/29 19:23:05 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static	int	ends(const char *str, char c, int n);
static	int	begins(const char *str, char c, int n);

char	**ft_split(char const *s, char c)
{
	char	**ssp;
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = ft_strtrim(s, &c); // ripulisco s dai separatori all'inizio e alla fine
	i = begins(str, c, j); // prendo il numero 
	ssp[j] = ft_calloc(i - j + 1, sizeof (char));
	ssp[j] = ft_substr(str, j, i);
	j = ends(str, c, i);
	return (ssp);
}

static	int	begins(const char *str, char c, int n)
{
	int	i;

	i = n;
	while (ft_strchr(str, c) == 0) //conto il numero di caratteri diversi dal separatore
		i++;
	return (i);
}

static	int	ends(const char *str, char c, int n)
{
	int	i;

	i = n;
	while (ft_strchr(str, c) != 0)// conto i separatori;
		n++;
	return (i);
} */
#include "libft.h"

static int ends(const char *str, char c, int n);
static int begins(const char *str, char c, int n);

char **ft_split(char const *s, char c)
{
    char **ssp;
    char *str;
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    if (s == NULL)
        return (NULL);
    
    str = ft_strtrim(s, &c); // ripulisco s dai separatori all'inizio e alla fine
    
    // Alloco memoria per l'array di stringhe
    ssp = ft_calloc(10, sizeof(char *)); // Puoi adattare questa allocazione se sai quanti segmenti ci saranno
    
    while (str[i] != '\0') {
        // Trovo l'inizio della parola
        i = begins(str, c, i);

        // Trovo la fine della parola
        size_t start = i;
        i = ends(str, c, i);

        // Alloco memoria per la sottostringa e la copio
        ssp[j] = ft_substr(str, start, i - start);
        if (ssp[j] == NULL) {
            return (NULL); // Gestisci eventuali errori di allocazione
        }
        j++;
    }
    ssp[j] = NULL; // Aggiungi il NULL alla fine dell'array
    return (ssp);
}

static int begins(const char *str, char c, int n)
{
    // Salta i caratteri delimitatori
    while (str[n] != '\0' && str[n] == c)
        n++;
    return n;
}

static int ends(const char *str, char c, int n)
{
    // Trova la fine della parola, cioè il primo delimitatore
    while (str[n] != '\0' && str[n] != c)
        n++;
    return n;
}



int main(void)
{
    char *str = "Hello world this is a test";
    char **result;
    int i;

    result = ft_split(str, ' '); // Usa lo spazio come delimitatore

    if (result != NULL)
    {
        i = 0;
        while (result[i] != NULL)
        {
            printf("Word %d: %s\n", i, result[i]);
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
