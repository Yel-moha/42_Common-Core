/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:01:11 by yel-moha          #+#    #+#             */
/*   Updated: 2025/12/15 13:01:14 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static int	check_args(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		write(1, "Usage: ./client <pid> \"message\"\n", 33);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "Invalid PID\n", 12);
		return (-1);
	}
	return (pid);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*msg;
	int		i;

	pid = check_args(argc, argv);
	if (pid == -1)
		return (1);
	msg = argv[2];
	i = 0;
	while (msg[i])
		send_char(pid, (unsigned char)msg[i++]);
	send_char(pid, '\0');
	return (0);
}
