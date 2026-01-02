#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}
int is_builtin(char *cmd)
{
    if(!cmd)
        return (0);
    return(!ft_strcmp(cmd, "echo")
        || !ft_strcmp(cmd, "cd")
        || !ft_strcmp(cmd, "pwd")
        || !ft_strcmp(cmd, "export")
        || !ft_strcmp(cmd, "unset")
        || !ft_strcmp(cmd, "env")
        || !ft_strcmp(cmd, "exit"));
}

int run_builtin(t_cmd *cmd, t_shell *shell)
{
    if (!ft_strcmp(cmd->argv[0], "pwd"))
    {
        builtin_pwd();
        return (0);
    }
    else if (!ft_strcmp(cmd->argv[0], "echo"))
    {
        builtin_echo(cmd->argv);
        return (0);
    }
    else if (!ft_strcmp(cmd->argv[0], "cd"))
    {
        return builtin_cd(cmd->argv);
    }
    else if (!ft_strcmp(cmd->argv[0], "env"))
    {
        builtin_env(shell);
        return 0;
    }
    else if (!ft_strcmp(cmd->argv[0], "export"))
    {
        return builtin_export(shell, cmd->argv);
    }
    else if (!ft_strcmp(cmd->argv[0], "unset"))
    {
        return builtin_unset(cmd->argv, shell);
    }
        /*
    else if (!ft_strcmp(cmd->argv[0], "exit"))
    {
        builtin_exit(shell, cmd->argv);
        return shell->exit_code;
    }
        */
    return 1; // non è un builtin
}
