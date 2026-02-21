/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:21:59 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:22:00 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_target(char **argv, t_shell *shell)
{
	char	*target;

	if (!argv[1])
	{
		target = env_get_value(shell->envp_copy, "HOME");
		if (!target || !*target)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (NULL);
		}
		return (target);
	}
	return (argv[1]);
}

static int	change_and_update_pwd(char *target, char *oldpwd, t_shell *shell)
{
	char	cwd[4096];

	if (chdir(target) != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, target, ft_strlen(target));
		write(2, ": ", 2);
		perror("");
		return (0);
	}
	if (*oldpwd)
		update_env_var(shell, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(shell, "PWD", cwd);
	return (1);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*oldpwd;
	char	*target;

	if (argv[1] && argv[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	target = get_cd_target(argv, shell);
	if (!target)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup("");
	if (!change_and_update_pwd(target, oldpwd, shell))
	{
		free(oldpwd);
		return (1);
	}
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
		return ;
	ft_strlcpy(var_str, name, len1 + 1);
	var_str[len1] = '=';
	ft_strlcpy(var_str + len1 + 1, value, len2 + 1);
	export_var(shell, var_str);
	free(var_str);
}
