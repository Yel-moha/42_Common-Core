/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:25:27 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:25:28 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static char	**alloc_and_copy_envp(char **envp, int count)
{
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	copy[count] = NULL;
	while (count > 0)
	{
		count--;
		copy[count] = ft_strdup(envp[count]);
		if (!copy[count])
		{
			while (copy[++count])
				free(copy[count]);
			return (free(copy), NULL);
		}
	}
	return (copy);
}

char	**copy_envp(char **envp)
{
	int	count;

	if (!envp)
		return (NULL);
	count = count_envp(envp);
	return (alloc_and_copy_envp(envp, count));
}

// 2. Libera envp copiato
void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

// 3. Cerca variabile nell'envp
char	*env_get_value(char **envp, char *name)
{
	int	i;
	int	len;

	if (!envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
