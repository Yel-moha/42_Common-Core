#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char *str;
    char *lasfir;

    if (argc > 1)
    {
        // salto spazi iniziali
        while (argv[1][i] == ' ' || argv[1][i] == '\t')
            i++;

        // salvo l'inizio della prima parola
        int start = i;
        while (argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
            i++;
        int end = i;

        // copio la prima parola
        lasfir = malloc(end - start + 1);
        k = 0;
        while (start < end)
            lasfir[k++] = argv[1][start++];
        lasfir[k] = '\0';

        // skip spazi dopo la prima parola
        while (argv[1][i] == ' ' || argv[1][i] == '\t')
            i++;

        // stampa il resto delle parole
        int first = 0;
        while (argv[1][i])
        {
            // salta spazi multipli
            while (argv[1][i] == ' ' || argv[1][i] == '\t')
                i++;
            if (!argv[1][i])
                break;

            if (first)
                write(1, " ", 1);

            while (argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
            {
                write(1, &argv[1][i], 1);
                i++;
            }
            first = 1;
        }

        // stampa la prima parola salvata
        if (first)
            write(1, " ", 1);
        j = 0;
        while (lasfir[j])
        {
            write(1, &lasfir[j], 1);
            j++;
        }
        free(lasfir);
    }
    write(1, "\n", 1);
    return (0);
}
