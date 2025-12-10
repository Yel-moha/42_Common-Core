#include <stdio.h>
#include <stdlib.h>

/* int is_prime(int num)
{
    int i;
    int rest;

    i = 2;
    if(num == 2 || num == 3)
        return(1);
    while(i * i <= num)
    {
        rest = num % i;
        if(rest == 0)
            return(rest);
        i++;
    }
    //printf("%d*\n", num);
    return(rest);
}
 */
int is_prime(int num)
{
    int i = 2;
    int rest = 0;
    if(num == 2 || num == 3)
        return 1;
    while(i <= num/2)
    {
        rest = num % i;
        if(rest == 0)
        {
            //printf(" %d  non é primo \n", num);
            return (rest);
        }

        i++;
    }
   // printf("%d é un fattore primo \n", num);
    return (rest);
}

int main(int argc, char **argv)
{
    int i;
    int num;
    int rest;

    i = 1;
    rest = 0;
    if(argc == 2)
    {
        num = atoi(argv[1]);
        if(num == 1)
            printf("1");
        else
        {
            if(is_prime(num))
            {
                printf("%d", num);
            }
            else
            {
                while(i <= num / 2)
                {
                    rest = num % i;
                    if(rest == 0)
                    {
                        if(is_prime(i))
                        {
                            num = num / i;
                            printf("%d*", i);
                            if(is_prime(num))
                                    printf("%d", num);
                            i = 1;
                        }
                    }
                    i++;
                }
            }
            
        }
    }
    printf("\n");
    return (0);

}