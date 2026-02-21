/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:26:33 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:26:34 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_pipeline_child(t_cmd *current, t_shell *shell,
	t_cmd *cmds, t_pipe_state *ps)
{
	setup_child_pipes(ps->fd, ps->prev_fd, current);
	close_all_heredoc_fds_except_current(cmds, current);
	if (apply_redirections(current->redirs, shell) < 0)
		cleanup_and_exit_child(shell, cmds, 1);
	execve_or_builtin(current, shell, cmds);
	cleanup_and_exit_child(shell, cmds, 1);
}

static pid_t	spawn_pipeline_child(t_cmd *current,
	t_shell *shell, t_cmd *cmds, t_pipe_state *ps)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute_pipeline_child(current, shell, cmds, ps);
	return (pid);
}

void	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	t_pipe_state	ps;
	pid_t			last_pid;
	t_cmd			*current;
	int				fd[2];

	process_all_heredocs(cmds, shell);
	if (g_signal == SIGINT)
	{
		shell->exit_code = 130;
		close_heredoc_fds(cmds);
		return ;
	}
	ps.prev_fd = -1;
	current = cmds;
	while (current)
	{
		if (current->next)
			pipe(fd);
		ps.fd = fd;
		last_pid = spawn_pipeline_child(current, shell, cmds, &ps);
		close_parent_pipes(&ps.prev_fd, fd, current);
		current = current->next;
	}
	close_heredoc_fds(cmds);
	wait_all_and_set_exit(last_pid, shell);
}
