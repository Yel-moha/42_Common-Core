int		max(int* tab, unsigned int len)
{
    int massimo;
    unsigned int i;

    i = 0;
    massimo = tab[0];
    while(i < len - 1)
    {
        if(tab[i] > massimo)
            massimo = tab[i];
        i++;
    }
    return massimo;
}

/* #include <stdio.h>
int main(void)
{
    int tab[] = {-42,0,-5,-64,-2,-68,-1};
    printf("\n\n Il massimo della tab é: %d\n\n", max(tab, 4));
    return 0;

} */