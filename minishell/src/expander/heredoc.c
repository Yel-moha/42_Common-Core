/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:27:56 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:28:02 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_char_to_line(char **line)
{
	char	buf;
	ssize_t	ret;

	ret = read(STDIN_FILENO, &buf, 1);
	if (ret == 1)
	{
		if (buf == '\n')
			return (1);
		*line = append_char(*line, buf);
		if (!*line)
			return (-1);
	}
	else if (ret == 0)
	{
		if (ft_strlen(*line) == 0)
			return (2);
		return (3);
	}
	else if (errno == EINTR)
		return (-1);
	else
		return (-1);
	return (0);
}

static char	*read_heredoc_line(void)
{
	char	*line;
	int		status;

	write(1, "> ", 2);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		status = read_char_to_line(&line);
		if (status == 1 || status == 2 || status == 3 || status == -1)
		{
			if (status == -1 || status == 2)
			{
				free(line);
				return (NULL);
			}
			break ;
		}
	}
	return (line);
}

static void	process_heredoc_line(char *line, int fd, t_shell *shell, int expand)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_word(line, shell);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
	}
	else
	{
		write(fd, line, ft_strlen(line));
	}
	write(fd, "\n", 1);
}

static int	handle_heredoc_line(char *line, t_heredoc_ctx *ctx)
{
	if (g_signal == SIGINT)
	{
		ctx->shell->exit_code = 130;
		if (line)
			free(line);
		return (-1);
	}
	if (!line || ft_strcmp(line, ctx->delimiter) == 0)
	{
		if (line)
			free(line);
		return (-1);
	}
	process_heredoc_line(line, ctx->fd, ctx->shell, ctx->expand);
	if (!ctx->expand && line)
		free(line);
	return (0);
}

void	read_heredoc(char *delimiter, t_shell *shell, int fd)
{
	char			*line;
	t_heredoc_ctx	ctx;

	if (!delimiter || !shell)
		return ;
	setup_heredoc_sigaction();
	g_signal = 0;
	ctx.delimiter = delimiter;
	ctx.fd = fd;
	ctx.shell = shell;
	ctx.expand = heredoc_should_expand(delimiter);
	while (1)
	{
		line = read_heredoc_line();
		if (handle_heredoc_line(line, &ctx) == -1)
			break ;
	}
	restore_sigaction();
}
