/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:33:37 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:33:38 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_WORD)
			count++;
		tok = tok->next;
	}
	return (count);
}

char	**tokens_to_argv(t_token *tokens)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (count_words(tokens) + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (tokens && tokens->type != T_PIPE)
	{
		if (tokens->type == T_WORD)
			argv[i++] = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	argv[i] = NULL;
	return (argv);
}

static void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static void	free_redirs(t_redir *redirs)
{
	t_redir	*next;

	while (redirs)
	{
		next = redirs->next;
		if (redirs->heredoc_fd >= 0)
			close(redirs->heredoc_fd);
		free(redirs->target);
		free(redirs);
		redirs = next;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*next;

	while (cmds)
	{
		next = cmds->next;
		free_argv(cmds->argv);
		free_redirs(cmds->redirs);
		free(cmds);
		cmds = next;
	}
}
