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

static void	cleanup_and_exit(t_shell *shell)
{
	free_envp(shell->envp_copy);
	rl_clear_history();
	exit(shell->exit_code);
}

static void	execute_parsing_and_execution(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = lexer(line);
	if (!tokens)
	{
		printf("minishell: unclosed quotes\n");
		shell->exit_code = 2;
		return ;
	}
	cmd = parse_tokens(tokens);
	if (!cmd)
	{
		shell->exit_code = 2;
		free_tokens(tokens);
		return ;
	}
	expand_cmds(cmd, shell);
	free_tokens(tokens);
	execute_cmds(cmd, shell);
	free_cmds(cmd);
}

static void	process_input(char *line, t_shell *shell)
{
	execute_parsing_and_execution(line, shell);
	if (shell->should_exit)
		cleanup_and_exit(shell);
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
			cleanup_and_exit(shell);
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
