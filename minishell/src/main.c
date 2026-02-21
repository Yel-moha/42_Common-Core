/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:25:20 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/21 15:25:21 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

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
