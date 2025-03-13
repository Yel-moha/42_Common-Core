/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:50:51 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/13 21:51:21 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int handle_integer(int n)
{
    char    *str;
    int     len;

    str = ft_itoa(n);
    len = write(1, str, ft_strlen(str));
    free(str);
    return (len);
}
