/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:26:22 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:26:23 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc_fds(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC && redir->heredoc_fd >= 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	close_all_heredoc_fds_except_current(t_cmd *cmds, t_cmd *current)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC && redir->heredoc_fd >= 0)
			{
				if (cmd != current)
				{
					close(redir->heredoc_fd);
					redir->heredoc_fd = -1;
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

static void	setup_heredoc_redir(t_redir *redir, t_shell *shell)
{
	int		pipefd[2];
	int		saved_stdin;
	char	*delimiter;

	if (pipe(pipefd) < 0)
		return ;
	saved_stdin = dup(STDIN_FILENO);
	delimiter = strip_quotes(ft_strdup(redir->target));
	read_heredoc(delimiter, shell, pipefd[1]);
	free(delimiter);
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	process_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
				setup_heredoc_redir(redir, shell);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
