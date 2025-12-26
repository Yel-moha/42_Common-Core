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
/*
// Aggiungi in qualche file (lexer_utils.c)
int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || 
			c == '|' || c == '<' || c == '>');
}

void	handle_delimiter(t_token **tokens, char c)
{
	if (c == '|')
		add_token(tokens, new_token(T_PIPE, ft_strdup("|"), 0));
	else if (c == '<')
		add_token(tokens, new_token(T_REDIR_IN, ft_strdup("<"), 0));
	else if (c == '>')
		add_token(tokens, new_token(T_REDIR_OUT, ft_strdup(">"), 0));
	// Nota: per "<<" e ">>" devi gestire due caratteri consecutivi
	//       ma quella logica è più complessa
}
*/