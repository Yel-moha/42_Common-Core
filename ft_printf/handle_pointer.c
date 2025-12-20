/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:14:30 by yel-moha          #+#    #+#             */
/*   Updated: 2025/01/03 21:14:30 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_pointer(void *ptr)
{
	unsigned long	addr;
	int				printed_chars;

	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	addr = (unsigned long)ptr;
	printed_chars = write(1, "0x", 2);
	printed_chars += handle_hex(addr, 'x');
	return (printed_chars);
}
