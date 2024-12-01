/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:47:25 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/01 22:59:12 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* 
int main(void)
{	
	// Apri un file in scrittura
	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	if (fd == -1) // Controlla errori
		return 1;

	ft_putchar_fd('B', fd); // Scrive 'B' nel file "output.txt"
	close(fd); // Chiudi il file
	return 0;
}

 */