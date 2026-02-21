#include "minishell.h"

static int	apply_file_redir(int type, char *target)
{
	int	fd;

	if (type == T_REDIR_IN)
		fd = open(target, O_RDONLY);
	else if (type == T_REDIR_OUT)
		fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(target), -1);
	if (type == T_REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_redir *redirs, t_shell *shell)
{
	(void)shell;
	while (redirs)
	{
		if (redirs->type == T_REDIR_IN || redirs->type == T_REDIR_OUT
			|| redirs->type == T_REDIR_APPEND)
		{
			if (apply_file_redir(redirs->type, redirs->target) < 0)
				return (-1);
		}
		else if (redirs->type == T_HEREDOC)
		{
			dup2(redirs->heredoc_fd, STDIN_FILENO);
			close(redirs->heredoc_fd);
		}
		redirs = redirs->next;
	}
	return (0);
}
