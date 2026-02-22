/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:26:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:27:00 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin_or_exec(t_cmd *cmd, t_shell *shell,
	int *saved_stdin, int *saved_stdout)
{
	if (handle_empty_cmd(cmd, shell))
		return ;
	if (handle_builtin_cmd(cmd, shell))
		return ;
	exec_external_cmd(cmd, shell, saved_stdin, saved_stdout);
}
