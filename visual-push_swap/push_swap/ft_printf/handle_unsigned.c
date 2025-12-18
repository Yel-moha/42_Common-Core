/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:14:56 by yel-moha          #+#    #+#             */
/*   Updated: 2025/01/03 21:14:56 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_unsigned(unsigned int value)
{
	int	printed_chars;

	printed_chars = 0;
	if (value >= 10)
		printed_chars += handle_unsigned(value / 10);
	printed_chars += write(1, &("0123456789"[value % 10]), 1);
	return (printed_chars);
}
