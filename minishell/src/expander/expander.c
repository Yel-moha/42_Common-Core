#include "minishell.h"

char	*expand_word(char *word, t_shell *shell)
{
	t_state	state;
	int		i;
	char	*res;

	state = STATE_NORMAL;
	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			state = update_state(word[i], state);
			i++;
			continue;
		}
		if (word[i] == '$' && state != STATE_IN_SINGLE_QUOTE)
			res = expand_variable(res, word, &i, shell);
		else
			res = append_char(res, word[i++]);
	}
	free(word);
	return (res);
}
/*
void	expand_cmds(t_cmd *cmds, t_shell *shell)
{
	int	i;

	while (cmds)
	{
		i = 0;
		//i = 1;  // Inizia da 1, salta argv[0]
		while (cmds->argv && cmds->argv[i])
		{
			cmds->argv[i] = expand_word(cmds->argv[i], shell);
			i++;
		}
		cmds = cmds->next;
	}
}
*/

void	expand_cmds(t_cmd *cmds, t_shell *shell)
{
	int	i;
	char	**splitted;

	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			cmds->argv[i] = expand_word(cmds->argv[i], shell);
			i++;
		}
		// Se argv[0] contiene spazi, splittalo
		if (cmds->argv && cmds->argv[0] && ft_strchr(cmds->argv[0], ' '))
		{
			splitted = ft_split(cmds->argv[0], ' ');
			if (splitted)
			{
				// Sostituisci argv[0] con primo token
				free(cmds->argv[0]);
				cmds->argv[0] = splitted[0];
				// Aggiungi gli altri token
				i = 1;
				while (splitted[i])
				{
					add_arg_to_cmd(cmds, splitted[i]);
					i++;
				}
				free(splitted); // Solo array, non le stringhe
			}
		}
		cmds = cmds->next;
	}
}
void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_argv;
	int		i;

	// Conta argc attuale
	count = 0;
	while (cmd->argv && cmd->argv[count])
		count++;
	
	// Alloca nuovo array
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return;
	
	// Copia vecchi argv
	i = 0;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	
	// Aggiungi nuovo arg
	new_argv[count] = ft_strdup(arg);
	new_argv[count + 1] = NULL;
	
	// Libera vecchio array (ma non le stringhe - già copiate)
	if (cmd->argv)
		free(cmd->argv);
	
	cmd->argv = new_argv;
}