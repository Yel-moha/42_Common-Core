#include <unistd.h>
#include <stdio.h>

int ft_atoi(char *str)
{
    int n;
    int i;

    i = 0;
    n = 0;
    while(str[i] >= '0' && str[i] <= '9')
    {
        n = n * 10 + (str[i] - '0');
        i++;
    }
    return n;
}

int is_prime(int n)
{
    int i;
    int j;

    i = 2;
    j = 1;
    if(n == 1)
        return 0;
    while(i <= n/2)
    {
        j = n % i;
        if(j == 0)
            return 0;
        i++;
    }
    return 1;
}

void putnbr(int n)
{
    char c;
    if(n > 9)
        putnbr(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
}

int main(int argc, char **argv)
{
    int i;
    int sum;
    int m;

    if(argc == 2)
    {
        i = 2;
        sum = 0;
        m = ft_atoi(argv[1]);
        while(i <= m)
        {
            if(is_prime(i))
                sum = sum + i;
            i++;
        }
        putnbr(sum);
    }
    else
        write(1, "0", 1);
    write(1, "\n", 1);
    return 0;
}