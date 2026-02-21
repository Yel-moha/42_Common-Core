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

static void	split_argv_if_needed(t_cmd *cmds)
{
	char	**splitted;
	int		i;

	if (cmds->argv && cmds->argv[0] && ft_strchr(cmds->argv[0], ' '))
	{
		splitted = ft_split(cmds->argv[0], ' ');
		if (splitted)
		{
			if (splitted[0])
			{
				free(cmds->argv[0]);
				cmds->argv[0] = splitted[0];
				i = 1;
				while (splitted[i])
				{
					add_arg_to_cmd(cmds, splitted[i]);
					free(splitted[i]);
					i++;
				}
			}
			free(splitted);
		}
	}
}

void	expand_cmds(t_cmd *cmds, t_shell *shell)
{
	while (cmds)
	{
		expand_argv(cmds, shell);
		handle_empty_argv(cmds);
		expand_redirs(cmds, shell);
		split_argv_if_needed(cmds);
		cmds = cmds->next;
	}
}
