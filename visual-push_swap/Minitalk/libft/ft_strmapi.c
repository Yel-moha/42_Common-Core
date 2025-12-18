/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:58:14 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/01 22:23:11 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*map;
	size_t	len;
	size_t	j;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	map = ft_calloc(len + 1, sizeof(char));
	if (!map)
		return (NULL);
	j = 0;
	while (j < len)
	{
		map[j] = f(j, s[j]);
		j++;
	}
	return (map);
}

/* int	main(void)
{
	char	*str = "hello, world!";
	char	*result = ft_strmapi(str, to_upper);

	printf("Originale: %s\n", str);
	printf("Modificata: %s\n", result);

	free(result); // Libera la memoria allocata
	return (0);
}
 */