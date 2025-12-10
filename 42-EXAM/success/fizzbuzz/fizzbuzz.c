#include <unistd.h>

void put_nbr(int n)
{
    int res;
    char c;
    int j;

    j = 0;
    res = 0;
    int m = n;
    while (n > 0)
    {
        n = n/10;
        j++;
    }

    char *str[j];
    int i = 0;

    while(i < j)
    {
        res = m % 10;
        str[i] = res + 48;
        m = m/10;
        res = 0;
        i++;
    }
    j--;
    while ( j >= 0)
    {
        write (1, &str[j], 1);
        j--;
    }
}

int main(void)
{
    int     i;
    char    c;

    i = 1;
    while(i <= 100)
    {
        if(i % 15 == 0)
        {
            write(1, "fizzbuzz", 8);
            write(1, "\n", 1);
        }
        else if(i % 3 == 0)
        {
            write(1, "fizz", 4);
            write(1, "\n", 1);
        }
        else if(i % 5 == 0)
        {
            write(1, "buzz", 4);
            write(1, "\n", 1);
        }
        else
        {
            put_nbr(i);
            write(1, "\n", 1);
        }
        i++;
    }
    return (0);
}
