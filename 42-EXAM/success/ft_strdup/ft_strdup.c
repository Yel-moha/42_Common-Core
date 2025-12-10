#include <stdlib.h>

char    *ft_strdup(char *src)
{
    int i;
    char *new_str;

    i = 0;
    while(src[i])
        i++;
    new_str = malloc(sizeof(char) * (i + 1));
    if(!new_str)
        return(NULL);
    i = 0;
    while(src[i])
    {
        new_str[i] = src[i];
        i++;
    }
    new_str[i] = '\0';
    return (new_str);
}