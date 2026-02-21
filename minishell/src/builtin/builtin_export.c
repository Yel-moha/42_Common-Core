/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:22:26 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:22:27 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;

	if (!shell || !argv)
		return (1);
	i = 1;
	if (!argv[i])
	{
		print_export_env(shell);
		shell->exit_code = 0;
		return (0);
	}
	while (argv[i])
	{
		export_var(shell, argv[i]);
		i++;
	}
	return (shell->exit_code);
}
