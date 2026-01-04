#include "minishell.h"

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*oldpwd;
	char	cwd[4096];
    char    *target;
	
	if (argv[1] && argv[2])
    {
        write(2, "minishell: cd: too many arguments\n", 34);
        return (1);
    }
	if (!argv[1])
	{
		target = env_get_value(shell->envp_copy, "HOME");
		if (!target || !*target)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else
        target = argv[1];
	// 2. Salva vecchia directory
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup(""); // fallback
	
	// 3. Cambia directory
	if (chdir(target) != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, target, ft_strlen(target));
		write(2, ": ", 2);
		perror("");
		free(oldpwd);
		return (1);
	}
	
	// 4. Aggiorna OLDPWD
	if (*oldpwd)
		update_env_var(shell, "OLDPWD", oldpwd);
	
	// 5. Aggiorna PWD
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(shell, "PWD", cwd);
	
	free(oldpwd);
	return (0);
}
void	update_env_var(t_shell *shell, char *name, char *value)
{
	char	*var_str;
	int		len1;
	int		len2;
	
	len1 = ft_strlen(name);
	len2 = ft_strlen(value);
	var_str = malloc(len1 + len2 + 2);
	if (!var_str)
		return;
	
	ft_strlcpy(var_str, name, len1 + 1);
	var_str[len1] = '=';
	ft_strlcpy(var_str + len1 + 1, value, len2 + 1);
	
	export_var(shell, var_str);
	free(var_str);
}