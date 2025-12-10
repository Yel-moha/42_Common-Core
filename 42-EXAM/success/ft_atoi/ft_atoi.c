int	ft_atoi(const char *str)
{
    int n;
    int i;
    int j;

    i = 0;
    j = 1;
    n = 0;
    while(str[i] == ' ' || str[i] == '\t')
        i++;
    if(str[i] == '-')
    {
        j = -1;
        i++;
    }
    if(str[i] == '+')
        i++;
    while(str[i] >= '0' && str[i] <= '9')
    {
        n = n * 10 + (str[i] - '0');
        i++;
    }
    return(n * j);
}

/* #include <stdio.h>
int main(void)
{
    char *str = "       -123h  j";
    int n = ft_atoi(str);
    printf("\n\n  %d \n\n", n);
    return 0;

} */