#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    int k;

    if(argc == 2)
    {
        i = 0;
        while(argv[1][i])
        {
            k = 0;
            if(argv[1][i] >= 'A' && argv[1][i] <= 'Z')
            {
                j = argv[1][i] - 'A';
                while(k <= j)
                {
                    write(1, &argv[1][i], 1);
                    k++;
                }
            }
            else if(argv[1][i] >= 'a' && argv[1][i] <= 'z')
            {
                j = argv[1][i] - 'a';
                while(k <= j)
                {
                    write(1, &argv[1][i], 1);
                    k++;
                }
            }
            else
                write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return 0;
}