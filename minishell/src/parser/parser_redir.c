#include "minishell.h"

t_redir	*new_redir(t_token_type type, char *target)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->target = ft_strdup(target);
	r->heredoc_fd = -1;
	r->next = NULL;
	return (r);
}

void	add_redir(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*parse_redir(t_cmd *cmd, t_token *tok)
{
	if (!tok->next || tok->next->type != T_WORD)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (NULL);
	}
	add_redir(&cmd->redirs, new_redir(tok->type, tok->next->value));
	return (tok->next->next);
}

int	is_redir_token(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_HEREDOC || type == T_REDIR_APPEND);
}
