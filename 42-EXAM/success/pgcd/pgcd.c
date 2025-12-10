#include <stdlib.h>
#include <stdio.h>

int mcd(int a, int b) 
{
    int resto;

    while (b != 0) 
    {
        resto = a % b; // calcola il resto
        a = b;         // aggiorna a
        b = resto;     // aggiorna b
    }
    return a; // a contiene il MCD
}

int main(int argc, char **argv)
{
    int a;
    int b;
    int mc;

    if(argc == 3)
    {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        if(a <= 0 || b <= 0)
        {
            printf("\n");
            return 0;
        }
        mc = mcd(b, a);
        printf("%d",mc);
    }
    printf("\n");
    return 0;
}