#include <stdlib.h>

#include <stdio.h>


int count_words(char *str)
{
    int i;
    int words;

    i = 0;
    words = 0;
    while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    while(str[i])
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            words++;
            while(str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
                i++;
        }
        if(str[i])
            i++;
    }
    return (words);
}


char    **ft_split(char *str)
{
    char **new_str;
    int count;
    int i;
    int j;
    int k;
    int t;
    int s;

    i = j = k = t = s =0;
    count = count_words(str);
    new_str = malloc(sizeof(char *) * (count + 1));
    if(!new_str)
        return(NULL);
     while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;

    while(str[i])
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && k < count)
        {
            s = 0;
            t = i;
            while(str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0')
            {
                i++;
                j++;
            }
            new_str[k] = malloc(sizeof(char) * (j + 1));
            if(!new_str[k])
                return(NULL);
            while(t < i)
            {
                new_str[k][s] = str[t];
                t++;
                s++;
            }
            new_str[k][s] = '\0';
            k++;
        }
        i++;
        j = 0;
        t = 0;
    }
    new_str[k];
    return(new_str);
}

/* int main(int argc, char **argv)
{
    int n;
    char **splittata;

    int j,i = 0;
    n = count_words(argv[1]);
    printf("il numero di parole é %d\n\n", n);
    printf("Qui proviamo ft_split sulla argv[1]: \n\n");
    splittata = ft_split(argv[1]);
    while(i < n)
    {
        printf("la %d di splittatat é %s\n",i,splittata[i]);
        i++;
    }
    return 0;
} */