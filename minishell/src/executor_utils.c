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
