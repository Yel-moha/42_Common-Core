/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:27:27 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/01 22:46:17 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	j;

	if (!f)
		return ;
	if (!s)
		return ;
	j = 0;
	while (s[j])
	{
		f(j, &s[j]);
		j++;
	}
}
/* 
void to_upper_with_index(unsigned int index, char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c -= 32; // Converti in maiuscolo
	*c += index; // Aggiungi l'indice al carattere
}

int main(void)
{
	char str[] = "hello";
	ft_striteri(str, to_upper_with_index);
	printf("Risultato: %s\n", str);
	return 0;
}
 */