#include "minishell.h"

void	export_new_var(t_shell *shell, char *arg)
{
	env_add(shell, arg);
}
