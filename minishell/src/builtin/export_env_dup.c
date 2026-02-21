#include "minishell.h"

char	**env_dup(char **envp)
{
	int		i;
	char	**dup;

	i = 0;
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
