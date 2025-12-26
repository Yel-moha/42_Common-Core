#include "minishell.h"

void	read_heredoc(char *delimiter, char **envp, int fd)
{
	char	*line;
	int		expand;

	expand = heredoc_should_expand(delimiter);
	delimiter = strip_quotes(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (expand)
			line = expand_word(line, envp);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(delimiter);
}
