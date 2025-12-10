#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    int k;

    if(argc == 2)
    {
        i = 0;
        k = 0;
        while(argv[1][i])
            i++;
        i--;
        while(argv[1][k] == ' ' || argv[1][k] == '\t')
                k++;
        while(i >= k)
        {
            while(argv[1][i] == ' ' || argv[1][i] == '\t')
                i--;
            while(argv[1][i] != ' ' && argv[1][i] != '\t' && i >= k)
                i--;
            j = i + 1;
            while(argv[1][j] != ' ' && argv[1][j] != '\t' && argv[1][j])
            {
                write(1, &argv[1][j], 1);
                j++;
            }
            if(i > k)
                write(1, " ", 1);
            i--;
        }

    }
    write(1, "\n", 1);
    return 0;
}