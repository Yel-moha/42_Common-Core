#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int start;
    int end;

    i = 0;
    start = 0;
    end = 0;
    if(argc == 2)
    {
            while(argv[1][i] == ' ' || argv[1][i] == '\t')
                i++;
            while(argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
            {
                write(1, &argv[1][i], 1);
                i++;
            }
    }
    write(1, "\n", 1);
    return (0);
}