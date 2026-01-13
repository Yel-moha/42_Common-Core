#include "minishell.h"

static void	print_unset_error(char *arg)
{
	write(2, "minishell: unset: `", 19);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

static void	remove_env_var(t_shell *shell, char *arg)
{
	char	*key;
	int	index;
	key = get_key(arg);
	index = find_env_index(shell->envp_copy, key);
	if (index != -1)
		env_remove_at_index(shell, index);
	free(key);
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			print_unset_error(argv[i]);
			shell->exit_code = 1;
		}
		else
			remove_env_var(shell, argv[i]);
		i++;
	}
	return (shell->exit_code);
}

void	env_remove_at_index(t_shell *shell, int index)
{
	int	i;
	if (!shell || !shell->envp_copy || index < 0)
		return ;
	free(shell->envp_copy[index]);
	i = index;
	while (shell->envp_copy[i + 1])
	{
		shell->envp_copy[i] = shell->envp_copy[i + 1];
		i++;
	}
	shell->envp_copy[i] = NULL;
}
