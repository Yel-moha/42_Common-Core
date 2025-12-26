#include "minishell.h"

t_state	update_state(char c, t_state state)
{
	if (c == '\'' && state == STATE_NORMAL)
		return (STATE_IN_SINGLE_QUOTE);
	if (c == '\'' && state == STATE_IN_SINGLE_QUOTE)
		return (STATE_NORMAL);
	if (c == '"' && state == STATE_NORMAL)
		return (STATE_IN_DOUBLE_QUOTE);
	if (c == '"' && state == STATE_IN_DOUBLE_QUOTE)
		return (STATE_NORMAL);
	return (state);
}

void	handle_char(char *line, int i, t_state *state)
{
	*state = update_state(line[i], *state);
}
