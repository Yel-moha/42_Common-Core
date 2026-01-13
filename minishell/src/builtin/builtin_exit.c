#include "minishell.h"

int	get_sign(const char **s)
{
	int	neg;
	neg = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			neg = -1;
		(*s)++;
	}
	return (neg);
}

int	add_digit(long *val, int digit, int neg)
{
	long max;
	long min;
	max = 9223372036854775807L;
	min = -9223372036854775807L - 1;
	if ((neg == 1 && *val > (max - digit) / 10))
		return (0);
	if ((neg == -1 && -(*val) < (min + digit) / 10))
		return (0);
	*val = *val * 10 + digit;
	return (1);
}

int	ft_atol_safe(const char *s, long *res)
{
	long	val;
	int	neg;
	int	valid;
	val = 0;
	neg = get_sign(&s);
	valid = 1;
	while (*s && valid)
	{
		if (!ft_isdigit(*s))
			valid = 0;
		else
			valid = add_digit(&val, (*s - '0'), neg);
		s++;
	}
	if (!valid)
		return (0);
	*res = val * neg;

	return (1);
}

static void	print_exit_error(char *arg)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	long	res;
	int	valid;
	write(1, "exit\n", 5);
	if (!argv[1])
		exit(shell->exit_code);
	valid = ft_atol_safe(argv[1], &res);
	if (!valid)
	{
		print_exit_error(argv[1]);
		exit(2);
	}
	if (argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->exit_code = 1;
		return (1);
	}
	res = ((res % 256) + 256) % 256;
	exit(res);
}
