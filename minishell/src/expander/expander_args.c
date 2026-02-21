/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:27:05 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:27:06 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}

static char	**create_new_argv(char **old_argv, int count, char *new_arg)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_argv[i] = old_argv[i];
		i++;
	}
	new_argv[count] = ft_strdup(new_arg);
	new_argv[count + 1] = NULL;
	return (new_argv);
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		count;
	char	**new_argv;

	count = count_argv(cmd->argv);
	new_argv = create_new_argv(cmd->argv, count, arg);
	if (!new_argv)
		return ;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}
