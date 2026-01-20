#include "minishell.h"

int g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	(void)ac;
	(void)av;
	if (!envp)
		return (1);
	shell.envp_copy = copy_envp(envp);
	if (!shell.envp_copy)
		return (1);
	shell.exit_code = 0;
	shell.should_exit = 0;
	init_signals();
	prompt_loop(&shell);
	free_envp(shell.envp_copy);
	return (shell.exit_code);
}
