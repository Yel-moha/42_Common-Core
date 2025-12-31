#include "minishell.h"

// 1. Copia envp
char	**copy_envp(char **envp)
{
	char	**copy;
	int		i;
	
	if (!envp)
		return (NULL);
	
	// Conta quante variabili
	i = 0;
	while (envp[i])
		i++;
	
	// Alloca array
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	
	// Copia ogni stringa
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			// Se fallisce, libera tutto
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// 2. Libera envp copiato
void	free_envp(char **envp)
{
	int	i;
	
	if (!envp)
		return;
	
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
			return (envp[i] + len + 1);  // Ritorna il valore dopo '='
		i++;
	}
	return (NULL);  // Non trovata
}