#include "minishell.h"

static void	print_cmd_error(char *cmd, char *msg)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

static int	exec_error_status(char *cmd, char *path)
{
	DIR	*dir;

	if (!path || !*path)
		return (print_cmd_error(cmd, "command not found"), 127);
	if (access(path, F_OK) != 0)
		return (print_cmd_error(cmd, "No such file or directory"), 127);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (print_cmd_error(cmd, "Is a directory"), 126);
	}
	if (access(path, X_OK) != 0)
		return (print_cmd_error(cmd, "permission denied"), 126);
	return (0);
}

void	execve_or_builtin(t_cmd *cmd, t_shell *shell, t_cmd *cmds_root)
{
	char	*path;
	int		code;

	if (!cmd || !cmd->argv || !cmd->argv[0] || !*cmd->argv[0])
		cleanup_and_exit_child(shell, cmds_root, 1);
	if (is_builtin(cmd->argv[0]))
	{
		code = run_builtin(cmd, shell);
		cleanup_and_exit_child(shell, cmds_root, code);
	}
	path = find_command_path(cmd->argv[0], shell);
	code = exec_error_status(cmd->argv[0], path);
	if (code != 0)
	{
		free(path);
		cleanup_and_exit_child(shell, cmds_root, code);
	}
	reset_signals_in_child();
	execve(path, cmd->argv, shell->envp_copy);
	perror("minishell");
	free(path);
	cleanup_and_exit_child(shell, cmds_root, 126);
}

void	execve_or_die(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	int		code;

	path = find_command_path(cmd->argv[0], shell);
	code = exec_error_status(cmd->argv[0], path);
	if (code != 0)
	{
		free(path);
		cleanup_and_exit_child(shell, cmd, code);
	}
	reset_signals_in_child();
	execve(path, cmd->argv, shell->envp_copy);
	perror("execve");
	free(path);
	cleanup_and_exit_child(shell, cmd, 1);
}
