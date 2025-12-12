/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:37 by yel-moha          #+#    #+#             */
/*   Updated: 2024/12/13 21:49:19 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int handle_pointer(void *ptr)
{
    unsigned long addr;
    int printed_chars;

    addr = (unsigned long)ptr;
    printed_chars = write(1, "0x", 2);
    printed_chars += handle_hex(addr, 'x');

    return printed_chars;
}

