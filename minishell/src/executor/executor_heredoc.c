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

static void	heredoc_child_process(int *fd, int saved_stdin, char *delim,
	t_shell	*shell)
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
	int	fd[2];
	pid_t	pid;
	int	saved_stdin;
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

static void	setup_heredoc_redir(t_redir *redir, t_shell *shell)
{
	int	pipefd[2];
	int	saved_stdin;
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
