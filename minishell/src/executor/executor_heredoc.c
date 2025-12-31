#include "minishell.h"

int apply_heredoc(char *delimiter, t_shell *shell)
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) < 0)
        return (-1);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        read_heredoc(delimiter, shell, fd[1]);
        close(fd[1]);
        exit(0);
    }
    else
    {
        close(fd[1]);
        waitpid(pid, NULL, 0);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
    }
    return (0);
}
