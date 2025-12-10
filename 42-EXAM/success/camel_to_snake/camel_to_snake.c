#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    char c;

    if(argc == 2)
    {
        i = 0;
        while(argv[1][i])
        {
            if(argv[1][i] >= 'A' && argv[1][i] <= 'Z')
            {
                write(1, "_", 1);
                c = argv[1][i] + 32;
                write(1, &c, 1);
                i++;
            }
            else
            {
                write(1, &argv[1][i], 1);
                i++;
            }
        }
    }
    write(1, "\n", 1);
    return 0;
}