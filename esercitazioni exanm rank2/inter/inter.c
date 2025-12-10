#include <unistd.h>

int    is_in(char c, char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int    already_printed(char c, char *s, int limit)
{
    int i = 0;
    while (i < limit)
    {
        if (s[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    int i;

    if (argc == 3)
    {
        i = 0;
        while (argv[1][i])
        {
            if (is_in(argv[1][i], argv[2])
                && !already_printed(argv[1][i], argv[1], i))
                write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}
