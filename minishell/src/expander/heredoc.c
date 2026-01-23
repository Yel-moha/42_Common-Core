#include "minishell.h"
#include <errno.h>

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
}

static void	setup_heredoc_sigaction(struct sigaction *old)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, old);
}

static void	restore_sigaction(struct sigaction *old)
{
	sigaction(SIGINT, old, NULL);
}

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
	int	status;

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

static int	handle_heredoc_line(char *line, char *delimiter, int fd,
	t_shell *shell, int expand)
{
	if (g_signal == SIGINT)
	{
		shell->exit_code = 130;
		if (line)
			free(line);
		return (-1);
	}
	if (!line || ft_strcmp(line, delimiter) == 0)
	{
		if (line)
			free(line);
		return (-1);
	}
	process_heredoc_line(line, fd, shell, expand);
	if (!expand && line)
		free(line);
	return (0);
}

void	read_heredoc(char *delimiter, t_shell *shell, int fd)
{
	char			*line;
	int				expand;
	struct sigaction	old_sa;

	if (!delimiter || !shell)
		return ;
	setup_heredoc_sigaction(&old_sa);
	g_signal = 0;
	expand = heredoc_should_expand(delimiter);
	while (1)
	{
		line = read_heredoc_line();
		if (handle_heredoc_line(line, delimiter, fd, shell, expand) == -1)
			break ;
	}
	restore_sigaction(&old_sa);
}
