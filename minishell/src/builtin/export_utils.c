#include "minishell.h"

char **env_dup(char **envp)
{
	int	i;
	i = 0;
	char	**dup;
	while (envp[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		dup[i] = ft_strdup(envp[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	env_sort(char **env)
{
	int	i;
	int	j;
	char	*tmp;
	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_var(char *var)
{
	char	*eq_pos;
	write(1, "declare -x ", 11);
	eq_pos = ft_strchr(var, '=');
	if (eq_pos)
	{
		write(1, var, eq_pos - var);
		write(1, "=\"", 2);
		write(1, eq_pos + 1, ft_strlen(eq_pos + 1));
		write(1, "\"", 1);
	}
	else
		write(1, var, ft_strlen(var));
	write(1, "\n", 1);
}

void	print_export_env(t_shell *shell)
{
	char	**dup;
	int	i;
	dup = env_dup(shell->envp_copy);
	if (!dup)
		return ;
	env_sort(dup);
	i = 0;
	while (dup[i])
		print_export_var(dup[i++]);
	free_split(dup);
}

static void	print_export_error(char *arg, t_shell *shell)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	shell->exit_code = 1;
}

void	export_var(t_shell *shell, char *arg)
{
	char	*key;
	int	index;
	if (!is_valid_identifier(arg))
		return (print_export_error(arg, shell));
	if (!has_equal(arg))
		return ;
	key = get_key(arg);
	index = find_env_index(shell->envp_copy, key);
	if (index >= 0)
		env_replace(shell->envp_copy, index, arg);
	else
		env_add(shell, arg);
	free(key);
	shell->exit_code = 0;
}
