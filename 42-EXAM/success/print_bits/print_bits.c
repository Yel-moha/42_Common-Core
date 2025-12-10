#include <unistd.h>

void	print_bits(unsigned char octet)
{
    int n;
    int i;
    char c[9] = "00000000";
    int j = 7;

    i = 0;
    n = octet;
    while(n >= 0 && j >= 0)
    {
        i = n % 2;
        n = n / 2;
        c[j] = i + '0';
        j--;
    }
    j = 0;
    while(c[j])
    {
        write(1, &c[j], 1);
        j++;
    }
}
/* 
int main(void)
{
   // unsigned char octet;

    print_bits(9);
    write(1, "\n", 1);
    return 0;
} */