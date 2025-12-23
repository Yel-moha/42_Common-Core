#include "minishell.h"

void    execute_single_cmd(t_cmd *cmd, char **envp)
{
    pid_t pid;

    if(!cmd || !cmd->argv || !cmd->argv[0])
        return ;
    pid = fork();
    if (pid == 0)
    {
        execve(cmd->argv[0], cmd->argv, envp);
        perror(cmd->argv[0]);
        exit(1);
    }
    else if(pid > 0)
        waitpid(pid, NULL, 0);
    else
        perror("fork");
}
