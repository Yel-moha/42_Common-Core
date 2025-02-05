#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    // Apri il file "test.txt" in modalità di sola lettura
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Errore nell'apertura del file");
        return (1);
    }

    // Leggi il file linea per linea usando get_next_line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Linea letta: %s", line); // Stampa la linea letta
        free(line); // Libera la memoria allocata da get_next_line
    }

    // Chiudi il file descriptor
    close(fd);

    return (0);
}