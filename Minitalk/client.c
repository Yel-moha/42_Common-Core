/* client.c
 *
 * Client for Minitalk project.
 * Usage: ./client <server_pid> "message"
 *
 * Sends each character of the message bit by bit to server PID using signals:
 * - SIGUSR1 represents bit 0
 * - SIGUSR2 represents bit 1
 *
 * After the message content, the client sends a final '\0' byte to indicate
 * end of transmission (so the server can emit a newline).
 */
#include "minitalk.h"

/*
 * send_char:
 * invia un singolo carattere al server bit per bit
 * SIGUSR1 = 0, SIGUSR2 = 1
 * usleep(100) riduce il rischio di perdita segnali su Linux
 */
static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		usleep(100);
		i--;
	}
}

/*
 * main:
 * verifica argomenti
 * utilizza ft_atoi della tua libft
 * invia tutti i caratteri più il terminatore '\0'
 */
int	main(int argc, char **argv)
{
	int		pid;
	char	*msg;
	int		i;

	if (argc != 3)
	{
		write(1, "Usage: ./client <pid> \"message\"\n", 33);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "Invalid PID\n", 12);
		return (1);
	}
	msg = argv[2];
	i = 0;
	while (msg[i])
	{
		send_char(pid, (unsigned char)msg[i]);
		i++;
	}
	send_char(pid, '\0');
	return (0);
}
