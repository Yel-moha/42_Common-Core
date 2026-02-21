#include "minishell.h"

static void	handle_child_exit_signal(int sig, t_shell *shell)
{
	if (sig == SIGINT)
		shell->exit_code = 130;
	else if (sig == SIGQUIT)
	{
		shell->exit_code = 131;
		printf("Quit (core dumped)\n");
	}
	else
		shell->exit_code = 128 + sig;
}

static void	update_exit_from_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		handle_child_exit_signal(WTERMSIG(status), shell);
	g_signal = 0;
}

void	handle_builtin_or_exec(t_cmd *cmd, t_shell *shell,
	int *saved_stdin, int *saved_stdout)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd->argv[0]))
	{
		shell->exit_code = run_builtin(cmd, shell);
		return ;
	}
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
