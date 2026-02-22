/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_single_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:33:26 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:33:27 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int	count_argv_tokens(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_WORD)
			count++;
		else if (is_redir_token(tok->type))
		{
			tok = tok->next;
			if (!tok)
				break ;
		}
		tok = tok->next;
	}
	return (count);
}

static void	fill_argv_only(t_token *tok, char **argv)
{
	int	argc;

	argc = 0;
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_WORD)
			argv[argc++] = ft_strdup(tok->value);
		else if (is_redir_token(tok->type) && tok->next)
			tok = tok->next;
		tok = tok->next;
	}
	argv[argc] = NULL;
}

static int	fill_redirs_only(t_token *tok, t_cmd *cmd, char **argv)
{
	int	i;

	while (tok && tok->type != T_PIPE)
	{
		if (is_redir_token(tok->type))
		{
			if (!tok->next || tok->next->type != T_WORD)
			{
				write(2, "DEBUG: redir no target at ", 26);
				if (tok->next)
					write(2, "token=", 6);
				ft_putstr_fd("newline\n", 2);
				i = 0;
				while (argv[i])
					free(argv[i++]);
				return (-1);
			}
			add_redir(&cmd->redirs, new_redir(tok->type, tok->next->value));
			tok = tok->next;
		}
		tok = tok->next;
	}
	return (0);
}

t_cmd	*parse_single_cmd(t_token **tokens)
{
	t_cmd	*cmd;
	char	**argv;
	int		argc;

	cmd = new_cmd();
	argc = count_argv_tokens(*tokens);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd || !argv)
		return (free(cmd), NULL);
	fill_argv_only(*tokens, argv);
	if (fill_redirs_only(*tokens, cmd, argv) < 0)
		return (free(argv), free_cmds(cmd), NULL);
	cmd->argv = argv;
	while (*tokens && (*tokens)->type != T_PIPE)
		(*tokens) = (*tokens)->next;
	return (cmd);
}
