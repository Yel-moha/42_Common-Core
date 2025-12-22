#include "minishell.h"

t_token	*lexer(char *line)
{
	t_token	*tokens;
	int		i;
	int		start;
	t_state	state;

	tokens = NULL;
	i = 0;
	start = -1;
	state = STATE_NORMAL;
	while (line[i])
	{
		handle_char(line, i, &state);
		if (is_space(line[i]) && state == STATE_NORMAL)
			handle_word_end(&tokens, line, &start, i);
		else if (line[i] == '|' && state == STATE_NORMAL)
		{
			handle_word_end(&tokens, line, &start, i);
			add_token(&tokens, new_token(T_PIPE, ft_strdup("|")));
		}
		else if (start == -1)
			start = i;
		i++;
	}
	if (state != STATE_NORMAL)
	{
		free_tokens(tokens);
		return (NULL);
	}
	handle_word_end(&tokens, line, &start, i);
	return (tokens);
}
