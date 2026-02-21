#include "minishell.h"

void	process_all_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		process_heredocs(current, shell);
		current = current->next;
	}
}

void	setup_child_pipes(int *fd, int prev_fd, t_cmd *current)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

void	close_parent_pipes(int *prev_fd, int *fd, t_cmd *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

void	handle_pipeline_signal(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = 128 + WTERMSIG(status);
}

void	wait_all_and_set_exit(pid_t last_pid, t_shell *shell)
{
	int	status;

	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	handle_pipeline_signal(status, shell);
}
