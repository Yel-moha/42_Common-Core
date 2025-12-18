/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:14:19 by yel-moha          #+#    #+#             */
/*   Updated: 2025/01/12 17:49:25 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_integer(int n)
{
	char	*str;
	int		len;

	str = ft_itoa(n);
	len = write(1, str, ft_strlen(str));
	free(str);
	return (len);
}
