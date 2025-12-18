/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:31:52 by yel-moha          #+#    #+#             */
/*   Updated: 2025/01/12 17:47:30 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

int	ft_printf(const char *format, ...);

int	handle_string(char *str);
int	handle_integer(int n);
int	handle_char(char c);
int	handle_hex(unsigned long value, char specifier);
int	handle_unsigned(unsigned int value);
int	handle_pointer(void *ptr);

#endif
