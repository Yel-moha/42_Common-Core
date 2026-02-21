/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by youssef           #+#    #+#             */
/*   Updated: 2026/01/31 18:13:54 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal_interrupt(t_shell *shell)
{
	shell->exit_code = 130;
	g_signal = 0;
}

static void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static int	prepare_single_cmd(t_cmd *cmd, t_shell *shell,
	int *saved_stdin, int *saved_stdout)
{
	if (g_signal == SIGINT)
		return (handle_signal_interrupt(shell), -1);
	process_heredocs(cmd, shell);
	if (g_signal == SIGINT)
	{
		shell->exit_code = 130;
		return (-1);
	}
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redirs, shell) < 0)
	{
		shell->exit_code = 1;
		restore_fds(*saved_stdin, *saved_stdout);
		return (-1);
	}
	return (0);
}

void	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!cmd)
		return ;
	if (prepare_single_cmd(cmd, shell, &saved_stdin, &saved_stdout) < 0)
	{
		close_heredoc_fds(cmd);
		return ;
	}
	if (!cmd->argv || !cmd->argv[0] || !*cmd->argv[0])
		shell->exit_code = 0;
	else
		handle_builtin_or_exec(cmd, shell, &saved_stdin, &saved_stdout);
	restore_fds(saved_stdin, saved_stdout);
	close_heredoc_fds(cmd);
}
