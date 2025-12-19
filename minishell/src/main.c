#include "minishell.h"

int	g_signal = 0;

int	main(void)
{
	init_signals();
	prompt_loop();
	return (0);
}
