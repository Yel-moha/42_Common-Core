/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:24:29 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/18 16:38:18 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/* 
#include <stdio.h>
#include <ctype.h>
int main()
{
    int i;

    i = -1;
    while (i < 130)
    {
        if (ft_isascii(i) != isascii(i))
        {
            printf("Error at %d: ft_isascii = %d, isascii = %d\n", 
                i, ft_isascii(i), isascii(i));
            return (1);
        }
        i++;
    }
    printf("All tests passed!\n");
    return (0);
}
 */