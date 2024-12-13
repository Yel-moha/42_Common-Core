/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:51:34 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/13 21:52:42 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>

void	ft_putnbr_base(int nbr, char *base);
int		base_len(char *base);
int		is_valid_base(char *base);
void	ft_putnbr(int nb, int b, char *base);

void	ft_putnbr_base(int nbr, char *base)
{
	int	base_length;

	if (!is_valid_base(base))
		return ;
	base_length = base_len(base);
	if (nbr < 0)
	{
		write(1, "-", 1);
		if (nbr == -2147483648)
		{
			ft_putnbr(-(nbr / base_length), base_length, base);
			write(1, &base[-(nbr % base_length)], 1);
		}
		else
		{
			nbr = -nbr;
			ft_putnbr(nbr, base_length, base);
		}
	}
	else
	{
		ft_putnbr(nbr, base_length, base);
	}
}

int	base_len(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

int	is_valid_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (base_len(base) <= 1)
}
/* 
int main(void)
{
    int nbr = 123456789;
    char base[] = "0123456789abcdef";
    ft_putnbr_base(nbr, base);
    return 0;
}

 */