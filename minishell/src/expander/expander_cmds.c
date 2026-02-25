/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:27:14 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:27:15 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_argv(t_cmd *cmds, t_shell *shell)
{
	int	i;

	i = 0;
	while (cmds->argv && cmds->argv[i])
	{
		cmds->argv[i] = expand_word(cmds->argv[i], shell);
		i++;
	}
}

static void	handle_empty_argv(t_cmd *cmds)
{
	int	i;

	if (cmds->argv && cmds->argv[0] && !*cmds->argv[0])
	{
		free(cmds->argv[0]);
		i = 1;
		while (cmds->argv[i])
		{
			cmds->argv[i - 1] = cmds->argv[i];
			i++;
		}
		cmds->argv[i - 1] = NULL;
	}
}

static void	expand_redirs(t_cmd *cmds, t_shell *shell)
{
	t_redir	*redir;

	redir = cmds->redirs;
	while (redir)
	{
		if (redir->target && redir->type != T_HEREDOC)
			redir->target = expand_word(redir->target, shell);
		redir = redir->next;
	}
}

void	expand_cmds(t_cmd *cmds, t_shell *shell)
{
	while (cmds)
	{
		expand_argv(cmds, shell);
		handle_empty_argv(cmds);
		expand_redirs(cmds, shell);
		cmds = cmds->next;
	}
}
