/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:21:08 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/18 15:32:21 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
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
    while (i < 530)
    {
        if (ft_isdigit(i) != 0 && isdigit(i) == 0)
        {
            printf("Error with i = %d\n", i);
            return (1);
        }
        if (ft_isdigit(i) == 0 && isdigit(i) != 0)
        {
            printf("Error with i = %d\n", i);
            return (1);
        }
        i++;
    }
    printf("All tests passed successfully!\n");
    return (0);
}
*/
