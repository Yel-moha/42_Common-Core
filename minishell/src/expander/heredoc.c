#include "minishell.h"

void	read_heredoc(char *delimiter, t_shell *shell, int fd)
{
	char	*line;
	int	expand;
	if (!delimiter || !shell)
		return ;
	expand = heredoc_should_expand(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (expand)
			line = expand_word(line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}
