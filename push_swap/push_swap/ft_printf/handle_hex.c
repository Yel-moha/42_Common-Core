/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:37 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/13 21:49:19 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int handle_hex(unsigned int value, char specifier)
{
    char *hex_digits;
    int  printed_chars;

    if (specifier == 'x')
        hex_digits = "0123456789abcdef";
    else
        hex_digits = "0123456789ABCDEF";

    printed_chars = 0;

    if (value >= 16)
        printed_chars += handle_hex(value / 16, specifier);
    printed_chars += write(1, &hex_digits[value % 16], 1);

    return printed_chars;
}