#include <stdlib.h>
#include <stdio.h>

char	*ft_itoa(int nbr)
{
    char *str;
    int i;
    int n;
    int j;
    int rest;

    i = 0;
    j = 0;
    n = nbr;
    rest = 0;
    if(nbr < 0)
    {
        n = -1 * nbr;
        i++;
    }
    while(n > 0)
    {
        n = n / 10;
        i++;
    }
    if (nbr == 0)
        i = 1;
    str = malloc(sizeof(char) * (i + 1));
    if(!str)
        return(NULL);
    if (nbr == 0)
        str[0] = '0';
    if(nbr < 0)
    {
        str[0] = '-';
        nbr = -1 * nbr;
    }
    j = i;
    i--;
    while(nbr > 0)
    {
        rest = nbr %  10;
        nbr = nbr / 10;
        str[i] = rest + '0';
        i--; 
    }
    //printf("il carattere nulla lo vai a mette in ordine %d\n\n", j);
    str[j] = '\0';
    return str;
}

/* int main(void)
{
    int n = -12330;
    char *str;

    str = ft_itoa(n);
    printf("\n\n%d come stringa diventta %s \n\n",n,str);
    return 0;
} */