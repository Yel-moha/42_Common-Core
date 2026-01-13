#include "minishell.h"

static void	process_token_char(char *line, int *i, int *start,
	t_state	*state, t_token **tokens)
{
	handle_char(line, *i, state);
	if (is_space(line[*i]) && *state == STATE_NORMAL)
		handle_word_end(tokens, line, start, *i);
	else if (line[*i] == '|' && *state == STATE_NORMAL)
	{
		handle_word_end(tokens, line, start, *i);
		add_token(tokens, new_token(T_PIPE, ft_strdup("|")));
		(*i)++;
		return ;
	}
	else if (is_redir(line[*i]) && *state == STATE_NORMAL)
	{
		handle_word_end(tokens, line, start, *i);
		handle_redir(tokens, line, i);
		return ;
	}
	else if (*start == -1)
		*start = *i;
	(*i)++;
}

t_token	*lexer(char *line)
{
	t_token	*tokens;
	int	i;
	int	start;
	t_state	state;
	tokens = NULL;
	i = 0;
	start = -1;
	state = STATE_NORMAL;
	while (line[i])
		process_token_char(line, &i, &start, &state, &tokens);
	if (state != STATE_NORMAL)
		return (free_tokens(tokens), (t_token *)NULL);
	handle_word_end(&tokens, line, &start, i);
	return (tokens);
}
