#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}
