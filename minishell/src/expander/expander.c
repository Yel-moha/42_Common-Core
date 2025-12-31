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

void	expand_cmds(t_cmd *cmds, t_shell *shell)
{
	int	i;

	while (cmds)
	{
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			cmds->argv[i] = expand_word(cmds->argv[i], shell);
			i++;
		}
		cmds = cmds->next;
	}
}
