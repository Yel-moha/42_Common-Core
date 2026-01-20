#include "minishell.h"

void	cleanup_and_exit_child(t_shell *shell, t_cmd *cmds, int status)
{
	free_cmds(cmds);
	free_envp(shell->envp_copy);
	rl_clear_history();
	exit(status);
}

char	*get_env_value(char **envp, char *name)
{
	int	i;
	int	len;
	i = 0;

	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len)
			&& envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*check_paths(char **paths, char *cmd)
{
	char	*path;
	char	*tmp;
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*result;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!get_env_value(shell->envp_copy, "PATH"))
		return (NULL);
	paths = ft_split(get_env_value(shell->envp_copy, "PATH"), ':');
	result = check_paths(paths, cmd);
	free_split(paths);
	return (result);
}

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
	int	code;

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

void	execute_cmds(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return ;
	if (cmds->next)
		execute_pipeline(cmds, shell);
	else
		execute_single_cmd(cmds, shell);
}

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

void	execve_or_die(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	int	code;

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
