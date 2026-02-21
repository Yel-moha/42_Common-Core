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
	int		i;

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

void	execute_cmds(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return ;
	if (cmds->next)
		execute_pipeline(cmds, shell);
	else
		execute_single_cmd(cmds, shell);
}
