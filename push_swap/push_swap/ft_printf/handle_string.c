/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:50:26 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/13 21:50:47 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int handle_string(char *str)
{
    int len = 0;

    if (!str)
        str = "(null)";
    while (str[len])
        len++;
    return write(1, str, len);
}