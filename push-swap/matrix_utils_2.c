#include "push_swap.h"
#include <stdlib.h>

// Crea una tabella di lookup per trovare velocemente la posizione di ogni numero in sorted[]
int *create_lookup_table(int *sorted, int size)
{
    int *lookup;
    int i;

    lookup = malloc(sizeof(int) * size);
    if (!lookup)
        exit(1);
    i = 0;
    while (i < size)
    {
        lookup[sorted[i]] = i;
        i++;
    }
    return (lookup);
}

#include <stdlib.h>

// Crea una tabella di lookup per trovare velocemente la posizione di ogni numero in sorted[]
static int *create_lookup_table(int *sorted, int size)
{
    int *lookup;
    int i;

    lookup = malloc(sizeof(int) * size);
    if (!lookup)
        exit(1);
    i = 0;
    while (i < size)
    {
        lookup[sorted[i]] = i;
        i++;
    }
    return (lookup);
}