#include "minishell.h"

int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_key(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
}

int	find_env_index(char **envp, char *key)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], key, key_len)
			&& (envp[i][key_len] == '\0'
			|| envp[i][key_len] == '='))
			return (i);
		i++;
	}
	return (-1);
}

void	env_add(t_shell *shell, char *new_var)
{
	int			i;
	char		**new_env;

	i = 0;
	while (shell->envp_copy[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (shell->envp_copy[i])
	{
		new_env[i] = shell->envp_copy[i];
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free(shell->envp_copy);
	shell->envp_copy = new_env;
}

void	env_replace(char **envp, int index, char *new_var)
{
	free(envp[index]);
	envp[index] = ft_strdup(new_var);
}
