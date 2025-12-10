#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;

    if(argc == 4)
    {
        i = 0;
        j = 0;
        while(argv[2][i])
            i++;
        while(argv[3][j])
            j++;
        i = 0;
        if(i > 1 || j > 1)
        {
            write(1, "\n", 1);
            return 0;
        }
        while(argv[1][i])
        {
            if(argv[1][i] == argv[2][0])
                write(1, &argv[3][0], 1);
            else
                write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return 0;
}