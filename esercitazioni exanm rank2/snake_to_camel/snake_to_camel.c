#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;
    char c;

    i = 0;
    if(argc == 2)
    {
        while(argv[1][i])
        {
            if(argv[1][i] == '_')
            {
                i++;
                c = argv[1][i] - 32;
                write(1, &c, 1);
            }
            else
                write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return(0);
}