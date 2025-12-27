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
int is_redir(char c)
{
    return (c == '<' || c == '>');
}

int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}
int is_double_redir(char *line, int i)
{
    if (!line[i + 1])
        return (0);
    return ((line[i] == '<' && line[i + 1] == '<')
        || (line[i] == '>' && line[i + 1] == '>'));
}
