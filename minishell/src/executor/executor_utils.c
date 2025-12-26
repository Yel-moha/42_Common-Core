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
