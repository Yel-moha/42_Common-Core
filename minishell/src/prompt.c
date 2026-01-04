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
void	prompt_loop(t_shell *shell)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmd;

	//rl_bind_key('\t', rl_insert); volendo disabilitare tab nella compilazione minishell
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		
		// Se line vuota o solo spazi: salta
		if (*line == '\0' || only_spaces(line))
		{
			free(line);
			continue;
		}
		
		// Altrimenti aggiungi a history e processa
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
