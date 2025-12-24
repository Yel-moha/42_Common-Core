/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:51 by yel-moha          #+#    #+#             */
/*   Updated: 2024/11/18 16:15:34 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1024);
	else
		return (0);
}
/*
 int main(void)
 {
    int verify;
    char c;
    c = 'A';

    verify = isalpha(c);
    if (verify == 1)
        printf(" Hai inserito una lettera dell'alfabeto");
    else
        printf(" il carattere inserito non e' parte dell'alfabeto ");
    return(0);
 }
 */
