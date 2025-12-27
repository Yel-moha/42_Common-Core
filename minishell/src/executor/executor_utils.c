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

char    *find_command_path(char *cmd, char **envp)
{
    char    **paths;
    char    *path;
    char    *tmp;
    int i;

    if(ft_strchr(cmd, '/'))
        return(ft_strdup(cmd));
    if (!get_env_value(envp, "PATH"))
        return (NULL);
    paths = ft_split(get_env_value(envp, "PATH"), ':');
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
#include "minishell.h"

void execve_or_builtin(t_cmd *cmd, char **envp)
{
    char    *path;

    if (!cmd || !cmd->argv || !cmd->argv[0])
        exit(1);

    if (is_builtin(cmd->argv[0]))
        exit(run_builtin(cmd, envp));

    path = find_command_path(cmd->argv[0], envp);
    if (!path)
    {
        write(2, "minishell: ", 11);
        write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
        write(2, ": command not found\n", 20);
        exit(127);
    }
    execve(path, cmd->argv, envp);
    perror("minishell");
    free(path);
    exit(126);
}

void execute_cmds(t_cmd *cmds, char **envp)
{
    if (!cmds)
        return ;
    if (cmds->next)
        execute_pipeline(cmds, envp);
    else
        execute_single_cmd(cmds, envp);
}

int apply_redirections(t_redir *redirs, char **envp)
{
    int fd;

    while (redirs)
    {
        if (redirs->type == T_REDIR_IN)
        {
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
            if (apply_heredoc(redirs->target, envp) < 0)
                return (-1);
        }
        redirs = redirs->next;
    }
    return (0);
}

void execve_or_die(t_cmd *cmd, char **envp)
{
    char *path;

    path = find_command_path(cmd->argv[0], envp);
    if (!path)
    {
        write(2, "minishell: command not found\n", 29);
        exit(127);
    }
    execve(path, cmd->argv, envp);
    perror("execve");
    exit(1);
}
