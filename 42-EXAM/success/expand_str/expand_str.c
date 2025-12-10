#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    if(argc == 2)
    {
        i = 0;
        j = 0;
        while(argv[1][j])
            j++;
        j--;
        while(argv[1][j] == ' ' || argv[1][j] == '\t')
            j--;
        while(argv[1][i] == ' ' || argv[1][i] == '\t')
            i++;
        while(argv[1][i] && i <= j)
        {
            if(argv[1][i] == ' ' || argv[1][i] == '\t')
            {
                write(1, "   ", 3);
                while(argv[1][i] == ' ' || argv[1][i] == '\t')
                    i++;
                i--;
            }
            else
                write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return 0;
}