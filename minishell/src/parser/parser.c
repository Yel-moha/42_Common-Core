#include "minishell.h"

static int	pipe_newline_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 1);
	ft_putendl_fd("`newline'", 1);
	return (-1);
}

static int	pipe_error(void)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	return (-1);
}

static int	validate_pipes(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == T_PIPE)
		return (pipe_error());
	while (tokens)
	{
		if (tokens->type == T_PIPE)
		{
			if (!tokens->next)
				return (pipe_newline_error());
			if (tokens->next->type == T_PIPE)
				return (pipe_error());
		}
		tokens = tokens->next;
	}
	return (0);
}

/*
static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->next = NULL;
	return (cmd);
}
*/
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*last;
	t_cmd	*cmd;

	if (validate_pipes(tokens) < 0)
		return (NULL);
	cmds = NULL;
	last = NULL;
	while (tokens)
	{
		cmd = parse_single_cmd(&tokens);
		if (!cmd)
			return (NULL);
		if (!cmds)
			cmds = cmd;
		else
			last->next = cmd;
		last = cmd;
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}
