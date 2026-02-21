#include "minishell.h"

static void	print_exit_error(char *arg)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
}

static void	handle_invalid_arg(t_shell *shell)
{
	write(2, "minishell: exit: too many arguments\n", 36);
	shell->exit_code = 1;
}

static int	validate_and_set_exit_code(char **argv, t_shell *shell)
{
	long	res;
	int		valid;

	valid = ft_atol_safe(argv[1], &res);
	if (!valid)
	{
		print_exit_error(argv[1]);
		shell->exit_code = 2;
		return (0);
	}
	if (argv[2])
	{
		handle_invalid_arg(shell);
		return (0);
	}
	res = ((res % 256) + 256) % 256;
	shell->exit_code = res;
	return (1);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	write(1, "exit\n", 5);
	if (!argv[1])
	{
		shell->should_exit = 1;
		return (shell->exit_code);
	}
	validate_and_set_exit_code(argv, shell);
	shell->should_exit = 1;
	return (shell->exit_code);
}
