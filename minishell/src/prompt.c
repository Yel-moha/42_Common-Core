#include "minishell.h"

void	prompt_loop(t_shell *shell)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmd;

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
		if (!tokens)
		{
			printf("minishell: unclosed quotes\n");
			free(line);
			continue ;
		}
		cmd = parse_tokens(tokens);
		//print_tokens(tokens);   // debug
		//print_cmds(cmd);        // debug
		expand_cmds(cmd, shell);
		execute_cmds(cmd, shell);
		free_cmds(cmd);
		free_tokens(tokens);
		free(line);
	}
}
