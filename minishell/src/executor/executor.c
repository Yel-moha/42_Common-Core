#include "minishell.h"

static void	handle_signal_interrupt(t_shell *shell)
{
	shell->exit_code = 130;
	g_signal = 0;
	printf("\n");
}

static void	handle_child_exit_signal(int sig, t_shell *shell)
{
	if (sig == SIGINT)
	{
		shell->exit_code = 130;
		printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		shell->exit_code = 131;
		printf("Quit (core dumped)\n");
	}
	else
		shell->exit_code = 128 + sig;
}

static void	handle_builtin_or_exec(t_cmd *cmd, t_shell *shell, int *saved_stdin,
	int	*saved_stdout)
{
	pid_t	pid;
	int	status;

	if (is_builtin(cmd->argv[0]))
	{
		shell->exit_code = run_builtin(cmd, shell);
	}
	else
	{
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
			if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				handle_child_exit_signal(WTERMSIG(status), shell);
			g_signal = 0;
		}
		else
			perror("fork");
	}
}

static void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	if (!cmd || !cmd->argv || !cmd->argv[0] || !*cmd->argv[0])
		return ;
	if (g_signal == SIGINT)
		return (handle_signal_interrupt(shell));
	process_heredocs(cmd, shell);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redirs, shell) < 0)
	{
		shell->exit_code = 1;
		restore_fds(saved_stdin, saved_stdout);
		return ;
	}
	handle_builtin_or_exec(cmd, shell, &saved_stdin, &saved_stdout);
	restore_fds(saved_stdin, saved_stdout);
	close_heredoc_fds(cmd);
}

static void	process_all_heredocs(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;
	current = cmds;
	while (current)
	{
		process_heredocs(current, shell);
		current = current->next;
	}
}

static void	setup_child_pipes(int *fd, int prev_fd, t_cmd *current)
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

static void	close_parent_pipes(int *prev_fd, int *fd, t_cmd *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

static void	handle_pipeline_signal(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = 128 + WTERMSIG(status);
}

static pid_t	spawn_pipeline_child(int *fd, int prev_fd, t_cmd *current,
	t_shell	*shell, t_cmd *cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_pipes(fd, prev_fd, current);
		close_all_heredoc_fds_except_current(cmds, current);
		if (apply_redirections(current->redirs, shell) < 0)
			exit(1);
		execve_or_builtin(current, shell);
		exit(1);
	}
	return (pid);
}

static void	wait_all_and_set_exit(pid_t last_pid, t_shell *shell)
{
	int	status;
	waitpid(last_pid, &status, 0);
	while (wait(NULL) > 0)
		;
	handle_pipeline_signal(status, shell);
}

void	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int	fd[2];
	int	prev_fd;
	pid_t	last_pid;
	t_cmd	*current;
	
	process_all_heredocs(cmds, shell);
	prev_fd = -1;
	current = cmds;
	while (current)
	{
		if (current->next)
			pipe(fd);
		last_pid = spawn_pipeline_child(fd, prev_fd, current, shell, cmds);
		close_parent_pipes(&prev_fd, fd, current);
		current = current->next;
	}
	close_heredoc_fds(cmds);
	wait_all_and_set_exit(last_pid, shell);
}
