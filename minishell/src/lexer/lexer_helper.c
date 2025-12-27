#include "minishell.h"

void	handle_redir(t_token **tokens, char *line, int *i)
{
	if (is_double_redir(line, *i))
	{
		if (line[*i] == '<')
			add_token(tokens, new_token(T_HEREDOC, ft_strdup("<<")));
		else
			add_token(tokens, new_token(T_REDIR_APPEND, ft_strdup(">>")));
		*i += 2;
	}
	else
	{
		if (line[*i] == '<')
			add_token(tokens, new_token(T_REDIR_IN, ft_strdup("<")));
		else
			add_token(tokens, new_token(T_REDIR_OUT, ft_strdup(">")));
		(*i)++;
	}
}
