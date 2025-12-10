#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    char c;

    if (argc < 2)
    {
        write(1, "\n", 1);
        return (0);
    }

    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            c = argv[i][j];

            /* se è lettera → rendi minuscola */
            if (c >= 'A' && c <= 'Z')
                c += 32;

            /* se è una lettera ed è l'ultima della parola → rendi maiuscola */
            if ((argv[i][j] >= 'a' && argv[i][j] <= 'z') ||
                (argv[i][j] >= 'A' && argv[i][j] <= 'Z'))
            {
                if (argv[i][j + 1] == ' ' || argv[i][j + 1] == '\t' || argv[i][j + 1] == '\0')
                    c = argv[i][j] & ~32;
            }

            write(1, &c, 1);
            j++;
        }

        write(1, "\n", 1);
        i++;
    }
    return (0);
}
