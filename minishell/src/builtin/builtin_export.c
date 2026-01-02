#include "minishell.h"

int builtin_export(t_shell *shell, char **argv)
{
    int i = 1;

    if (!argv[i])
    {
        print_export_env(shell);
        shell->exit_code = 0;
        return 0;
    }

    while (argv[i])
    {
        export_var(shell, argv[i]);
        i++;
    }
    return shell->exit_code;
}
