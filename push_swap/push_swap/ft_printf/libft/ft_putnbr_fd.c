/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:29:26 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/04 20:38:53 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 0)
	{
		if (n >= 10)
			ft_putnbr_fd(n / 10, fd);
		write(fd, &"0123456789"[n % 10], 1);
	}
}
/* int main(void)
{	
	// Apri un file in scrittura
	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	if (fd == -1) // Controlla errori
		return 1;

	ft_putnbr_fd(102364, fd); // Scrive 'B' nel file "output.txt"
	close(fd); // Chiudi il file
	return 0;
}  */