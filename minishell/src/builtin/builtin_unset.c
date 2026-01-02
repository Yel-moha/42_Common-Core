#include "minishell.h"

int builtin_unset(char **argv, t_shell *shell)
{
    int i;
    int index;
    char *key;

    i = 1;
    while (argv[i])
    {
        if (!is_valid_identifier(argv[i]))
        {
            write(2, "minishell: unset: `", 19);
            write(2, argv[i], ft_strlen(argv[i]));
            write(2, "': not a valid identifier\n", 26);
            shell->exit_code = 1;
        }
        else
        {
            key = get_key(argv[i]);
            index = find_env_index(shell->envp_copy, key);
            if (index != -1)
                env_remove_at_index(shell, index);
            free(key);
        }
        i++;
    }
    return (shell->exit_code);
}

void env_remove_at_index(t_shell *shell, int index)
{
    int i;

    if (!shell || !shell->envp_copy || index < 0)
        return;

    free(shell->envp_copy[index]);

    i = index;
    while (shell->envp_copy[i + 1])
    {
        shell->envp_copy[i] = shell->envp_copy[i + 1];
        i++;
    }
    shell->envp_copy[i] = NULL;
}
