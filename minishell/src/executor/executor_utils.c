#include "minishell.h"

char    *get_env_value(char **envp, char *name)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(name);
    while(envp[i])
    {
        if(!ft_strncmp(envp[i], name, len)
            && envp[i][len] == '=')
            return (envp[i] + len + 1);
        i++;
    }
    return (NULL);
}

char    *find_command_path(char *cmd, t_shell *shell)
{
    char    **paths;
    char    *path;
    char    *tmp;
    int i;

    if(ft_strchr(cmd, '/'))
        return(ft_strdup(cmd));
    if (!get_env_value(shell->envp_copy, "PATH"))
        return (NULL);
    paths = ft_split(get_env_value(shell->envp_copy, "PATH"), ':');
    i = 0;
    while(paths && paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        path = ft_strjoin(tmp, cmd);
        free(tmp);
        if(access(path, X_OK)== 0)
            return(free_split(paths), path);
        free(path);
        i++;
    }
    free_split(paths);
    return(NULL);
}

void execve_or_builtin(t_cmd *cmd, t_shell *shell)
{
    char    *path;

    if (!cmd || !cmd->argv || !cmd->argv[0] || !*cmd->argv[0])
        exit(1);

    if (is_builtin(cmd->argv[0]))
        exit(run_builtin(cmd, shell));

    path = find_command_path(cmd->argv[0], shell);
    if (!path)
    {
        write(2, "minishell: ", 11);
        write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
        write(2, ": command not found\n", 20);
        exit(127);
    }
    reset_signals_in_child();
    execve(path, cmd->argv, shell->envp_copy);
    perror("minishell");
    free(path);
    exit(126);
}

void execute_cmds(t_cmd *cmds, t_shell *shell)
{
    if (!cmds)
        return ;
    if (cmds->next)
        execute_pipeline(cmds, shell);
    else
        execute_single_cmd(cmds, shell);
}

int apply_redirections(t_redir *redirs, t_shell *shell)
{
    int fd;
    (void)shell;
    while (redirs)
    {
        if (redirs->type == T_REDIR_IN)
        {
            //printf("DEBUG: opening file: [%s]\n", redirs->target);
            fd = open(redirs->target, O_RDONLY);
            if (fd < 0)
                return (perror(redirs->target), -1);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (redirs->type == T_REDIR_OUT)
        {
            fd = open(redirs->target,
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                return (perror(redirs->target), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redirs->type == T_REDIR_APPEND)
        {
            fd = open(redirs->target,
                O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
                return (perror(redirs->target), -1);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (redirs->type == T_HEREDOC)
        {
            dup2(redirs->heredoc_fd, STDIN_FILENO);
            close(redirs->heredoc_fd);
        }
        redirs = redirs->next;
    }
    return (0);
}
/*
static void    exec_error(char *cmd, char *path)
{
    if (!path)
    {
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": command not found\n", 20);
        exit(127);
    }
    if (access(path, F_OK) != 0)
    {
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": No such file or directory\n", 28);
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
*/

static void    exec_error(char *cmd, char *path)
{
    DIR *dir;

    if (!path || !*path)
    {
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": command not found\n", 20);
        exit(127);
    }
    if (access(path, F_OK) != 0)
    {
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": No such file or directory\n", 28);
        exit(127);
    }
    // Controlla se è directory
    dir = opendir(path);
    if (dir)
    {
        closedir(dir);
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": Is a directory\n", 18);
        exit(126);
    }
    if (access(path, X_OK) != 0)
    {
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": permission denied\n", 20);
        exit(126);
    }
}

void execve_or_die(t_cmd *cmd, t_shell *shell)
{
    char *path;

    path = find_command_path(cmd->argv[0], shell);
    /*
    if (!path)
    {
        write(2, "minishell: command not found\n", 29);
        exit(127);
    }
    */
    exec_error(cmd->argv[0], path);
    reset_signals_in_child();
    execve(path, cmd->argv, shell->envp_copy);
    perror("execve");
    exit(1);
}
