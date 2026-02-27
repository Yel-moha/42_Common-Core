/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single_exec_exit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 00:00:00 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/27 18:01:08 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_exit_signal(int sig, t_shell *shell)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		shell->exit_code = 130;
	}
	else if (sig == SIGQUIT)
	{
		shell->exit_code = 131;
		write(1, "Quit (core dumped)\n", 19);
	}
	else
		shell->exit_code = 128 + sig;
}

void	update_exit_from_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		handle_child_exit_signal(WTERMSIG(status), shell);
	g_signal = 0;
}
