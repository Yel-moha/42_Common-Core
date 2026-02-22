/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single_exec_helpers.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 00:00:00 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/22 00:00:00 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_empty_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->argv || !cmd->argv[0])
	{
		shell->exit_code = 0;
		return (1);
	}
	return (0);
}

int	handle_builtin_cmd(t_cmd *cmd, t_shell *shell)
{
	if (is_builtin(cmd->argv[0]))
	{
		shell->exit_code = run_builtin(cmd, shell);
		return (1);
	}
	return (0);
}

void	exec_external_cmd(t_cmd *cmd, t_shell *shell,
	int *saved_stdin, int *saved_stdout)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close(*saved_stdin);
		close(*saved_stdout);
		execve_or_die(cmd, shell);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		update_exit_from_status(status, shell);
	}
	else
		perror("fork");
}
