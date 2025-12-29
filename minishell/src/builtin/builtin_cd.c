#include "minishell.h"

int	builtin_cd(char **argv)
{
    if(!argv[1])
    {
        write(2, "minishell: cd: missing argument\n", 32);
        return (1);
    }
    if(argv[2])
    {
        write(2, "minishell: cd: too many arguments\n", 34);
        return (1);
    }
    if(chdir(argv[1]) != 0)
    {
        write(2, "minishell: cd: ", 15);
        write(2, argv[1], ft_strlen(argv[1]));
        write(2, ": ", 2);
        perror("");
        return (1);
    }
    return (0);
}