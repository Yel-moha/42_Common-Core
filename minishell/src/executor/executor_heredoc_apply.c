/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc_apply.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:26:15 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:26:16 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_child_process(int *fd, int saved_stdin, char *delim,
	t_shell *shell)
{
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(fd[0]);
	read_heredoc(delim, shell, fd[1]);
	close(fd[1]);
	exit(0);
}

static void	heredoc_parent_process(int *fd, int saved_stdin, pid_t pid)
{
	close(fd[1]);
	waitpid(pid, NULL, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(saved_stdin);
}

int	apply_heredoc(char *delimiter, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	int		saved_stdin;

	if (pipe(fd) < 0)
		return (-1);
	saved_stdin = dup(STDIN_FILENO);
	pid = fork();
	if (pid == 0)
		heredoc_child_process(fd, saved_stdin, delimiter, shell);
	else
		heredoc_parent_process(fd, saved_stdin, pid);
	return (0);
}
