/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:23:09 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:23:54 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_equal(char *s)
{
	return (ft_strchr(s, '=') != NULL);
}

void	export_new_var(t_shell *shell, char *arg)
{
	env_add(shell, arg);
}
