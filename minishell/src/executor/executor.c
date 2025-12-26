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
    pid_t  pid;
    char   *path;
    int    status;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return ;

    if (is_builtin(cmd->argv[0]))
    {
        g_exit_status = run_builtin(cmd, envp);
        return ;
    }

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
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            g_exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_exit_status = 128 + WTERMSIG(status);
    }
    else
        perror("fork");

    free(path);
}

void execute_pipeline(t_cmd *cmds, char **envp)
{
    int     fd[2];
    int     prev_fd;
    pid_t   pid;
    //pid_t   last_pid;
    int     status;

    prev_fd = -1;
    while (cmds)
    {
        if (cmds->next)
            pipe(fd);

        pid = fork();
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmds->next)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            // redirections + heredoc QUI
            execve_or_builtin(cmds, envp);
            exit(1);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (cmds->next)
        {
            close(fd[1]);
            prev_fd = fd[0];
        }
        //last_pid = pid;
        cmds = cmds->next;
    }
    while (wait(&status) > 0)
        ;
    if (WIFEXITED(status))
        g_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_exit_status = 128 + WTERMSIG(status);
}
/*
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
    pid_t  pid;
    char   *path;
    int    status;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        return ;

    if (is_builtin(cmd->argv[0]))
    {
        g_exit_status = run_builtin(cmd, envp);
        return ;
    }

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
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            g_exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_exit_status = 128 + WTERMSIG(status);
    }
    else
        perror("fork");

    free(path);
}

static void	update_exit_status(int status)
{
    if (WIFEXITED(status))
        g_exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        g_exit_status = 128 + WTERMSIG(status);
}

void execute_pipeline(t_cmd *cmds, char **envp)
{
    int     fd[2];
    int     prev_fd;
    pid_t   pid;
    pid_t   last_pid;
    int     status;

    prev_fd = -1;
    last_pid = -1;
    while (cmds)
    {
        if (cmds->next && pipe(fd) == -1)
        {
            perror("pipe");
            return ;
        }

        pid = fork();
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmds->next)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            // redirections + heredoc QUI
            execve_or_builtin(cmds, envp);
            exit(1);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (cmds->next)
        {
            close(fd[1]);
            prev_fd = fd[0];
        }
        last_pid = pid;
        cmds = cmds->next;
    }
    if (last_pid > 0 && waitpid(last_pid, &status, 0) != -1)
        update_exit_status(status);
    while (wait(NULL) > 0)
        ;
}
*/