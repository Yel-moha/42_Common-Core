/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:32:47 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:32:48 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	update_state(char c, t_state state)
{
	if (c == '\'' && state == STATE_NORMAL)
		return (STATE_IN_SINGLE_QUOTE);
	if (c == '\'' && state == STATE_IN_SINGLE_QUOTE)
		return (STATE_NORMAL);
	if (c == '"' && state == STATE_NORMAL)
		return (STATE_IN_DOUBLE_QUOTE);
	if (c == '"' && state == STATE_IN_DOUBLE_QUOTE)
		return (STATE_NORMAL);
	return (state);
}

void	handle_char(char *line, int i, t_state *state)
{
	if (!line || !state)
		return ;
	*state = update_state(line[i], *state);
}
