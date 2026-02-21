/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:32:42 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:32:43 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir(t_token **tokens, char *line, int *i)
{
	if (!tokens || !line || !i)
		return ;
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
