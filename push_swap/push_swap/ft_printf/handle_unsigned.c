/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:37 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/13 21:49:19 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int handle_unsigned(unsigned int value)
{
    int printed_chars;

    printed_chars = 0;
    if (value >= 10)
        printed_chars += handle_unsigned(value / 10);
    printed_chars += write(1, &("0123456789"[value % 10]), 1);

    return printed_chars;
}