#include "minitalk.h"

volatile sig_atomic_t	g_state[2] = {0, 0};

static void	write_pid(void)
{
	char	buf[32];
	pid_t	pid;
	int		i;

	pid = getpid();
	i = 0;
	if (pid == 0)
		buf[i++] = '0';
	while (pid > 0)
	{
		buf[i++] = (pid % 10) + '0';
		pid /= 10;
	}
	while (i-- > 0)
		write(1, &buf[i], 1);
	write(1, "\n", 1);
}

static void	signal_handler(int signo)
{
	char	c;

	g_state[0] = (g_state[0] << 1) | (signo == SIGUSR2);
	g_state[1]++;
	if (g_state[1] == 8)
	{
		c = (char)g_state[0];
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		g_state[0] = 0;
		g_state[1] = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	write_pid();
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
