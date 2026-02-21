/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:25:56 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:33:56 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// funzione per debug cmds

void	print_cmds(t_cmd *cmds)
{
	int	i;

	while (cmds)
	{
		i = 0;
		printf("CMD:\n");
		while (cmds->argv && cmds->argv[i])
		{
			printf("  argv[%d] = %s\n", i, cmds->argv[i]);
			i++;
		}
		cmds = cmds->next;
	}
}

//funzione per debug tokens

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TOKEN type=%d value=%s\n",
			tokens->type,
			tokens->value);
		tokens = tokens->next;
	}
}
