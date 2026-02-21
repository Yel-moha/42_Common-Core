#include "minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
}

static struct sigaction	*heredoc_old_sa_storage(void)
{
	static struct sigaction	old_sa;

	return (&old_sa);
}

void	setup_heredoc_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, heredoc_old_sa_storage());
}

void	restore_sigaction(void)
{
	sigaction(SIGINT, heredoc_old_sa_storage(), NULL);
}
