#include "minishell.h"

static int	only_spaces(char *str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	process_input(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;
	tokens = lexer(line);
	if (!tokens)
	{
		printf("minishell: unclosed quotes\n");
		return ;
	}
	cmd = parse_tokens(tokens);
	if (!cmd)
	{
		free_tokens(tokens);
		return ;
	}
	expand_cmds(cmd, shell);
	execute_cmds(cmd, shell);
	free_cmds(cmd);
	free_tokens(tokens);
}

void	prompt_loop(t_shell *shell)
{
	char	*line;
	while (1)
	{
		g_signal = 0;
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line == '\0' || only_spaces(line))
		{
			free(line);
			continue;
		}
		add_history(line);
		process_input(line, shell);
		free(line);
	}
}
