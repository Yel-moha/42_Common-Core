#include "minishell.h"

void	prompt_loop(void)
{
	char	*line;
	t_token	*tokens;
	t_cmd *cmd;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		tokens = lexer(line);
		cmd = parse_tokens(tokens);
		if (!tokens)
		{
			printf("minishell: unclosed quotes\n");
			free(line);
			continue ;
		}
		print_tokens(tokens);
		print_cmds(cmd);
		free_tokens(tokens);
		free(line);
	}
}
