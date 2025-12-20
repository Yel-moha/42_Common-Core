#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_word(t_token **tokens, char *line, int start, int end)
{
	char	*word;

	if (end <= start)
		return ;
	word = ft_substr(line, start, end - start);
	add_token(tokens, new_token(T_WORD, word));
}

void	handle_word_end(t_token **tokens, char *line, int *start, int i)
{
	if (*start != -1)
		add_word(tokens, line, *start, i);
	*start = -1;
}
