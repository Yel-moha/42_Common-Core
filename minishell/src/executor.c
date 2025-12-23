#include "minishell.h"

static void    exec_error(char *cmd, char *path)
{
    if (!path)
    {
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": command not found\n", 20);
        exit(127);
    }
    if (access(path, X_OK) != 0)
    {
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": permission denied\n", 20);
        exit(126);
    }
}

void    execute_single_cmd(t_cmd *cmd, char **envp)
{
    pid_t    pid;
    char    *path;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return ;
    path = find_command_path(cmd->argv[0], envp);
    pid = fork();
    if (pid == 0)
    {
        exec_error(cmd->argv[0], path);
        execve(path, cmd->argv, envp);
        perror("minishell");
        exit(1);
    }
    else if (pid > 0)
        waitpid(pid, NULL, 0);
    else
        perror("fork");
    free(path);
}
