#include<unistd.h>

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while(str[i]) // volendo posso scrivere anche while(str[i] != '\0')
    {
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

int main(void)
{
    char *stringa;

    stringa = "ciao modo";
    ft_putstr(stringa);
}