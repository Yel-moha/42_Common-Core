#include "minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	init_signals();
	prompt_loop(envp);
	return (0);
}

