/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:22:10 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:22:11 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_shell *shell)
{
	int	i;

	if (!shell || !shell->envp_copy)
	{
		return ;
	}
	i = 0;
	while (shell->envp_copy[i])
	{
		if (ft_strchr(shell->envp_copy[i], '='))
		{
			write(1, shell->envp_copy[i], ft_strlen(shell->envp_copy[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	shell->exit_code = 0;
}
