/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:27:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:27:45 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_should_expand(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

char	*strip_quotes(char *s)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			res = append_char(res, s[i]);
		i++;
	}
	free(s);
	return (res);
}
