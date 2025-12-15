/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:17:57 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/04 20:38:39 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	size_t	i;

	i = 0;
	if (!s)
		return ;
	len = ft_strlen(s);
	while (i < len)
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

/* int main(void)
{	
	// Apri un file in scrittura
	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	if (fd == -1) // Controlla errori
		return 1;

	ft_putstr_fd("Baracca", fd); // Scrive 'B' nel file "output.txt"
	close(fd); // Chiudi il file
	return 0;
} */
