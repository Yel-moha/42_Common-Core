#include "push_swap.h"
#include <stdlib.h>

static int matrix_operations = 0;  // Contatore globale delle operazioni

// Crea una tabella di lookup per trovare velocemente la posizione di ogni numero in sorted[]
static int *create_lookup_table(int *sorted, int size)
{
    int *lookup;
    int i;
    int max_value = sorted[size - 1];  // Dato che sorted è ordinato

    if (!sorted)
    {
        ft_printf("❌ Errore: `sorted` è NULL in `create_lookup_table()`!\n");
        exit(1);
    }

    lookup = malloc(sizeof(int) * (max_value + 1));
    if (!lookup)
        exit(1);

    // Inizializza lookup con valori fuori dai limiti
    i = 0;
    while (i <= max_value)  // Fix: include max_value nell'inizializzazione
    {
        lookup[i] = -1;
        i++;
    }

    // Riempire lookup con indici normalizzati
    i = 0;
    while (i < size)
    {
        lookup[sorted[i]] = i;
        i++;
    }
    return (lookup);
}

static void write_matrix_ones(int **M, t_stack *stack, int *lookup)
{
    int i;
    int index;

    if (!M || !stack || !lookup)  // Fix: aggiungi controlli null pointer
    {
        ft_printf("❌ Errore: puntatori nulli in write_matrix_ones!\n");
        exit(1);
    }

    i = 0;
    while (i < stack->size_a)
    {
        if (stack->a[i] < 0 || stack->a[i] >= 1000)
        {
            ft_printf("❌ Errore: stack->a[%d] = %d fuori dai limiti!\n", i, stack->a[i]);
            exit(1);
        }

        index = lookup[stack->a[i]];
        if (index == -1)
        {
            ft_printf("❌ Errore: lookup[%d] non trovato!\n", stack->a[i]);
            exit(1);
        }

        if (index >= stack->size_a)  // Fix: verifica limiti dell'indice
        {
            ft_printf("❌ Errore: index %d fuori dai limiti!\n", index);
            exit(1);
        }

        M[i][index] = 1;
        matrix_operations++;  // Fix: incrementa il contatore
        i++;
    }
}

static void create_matrix(int **M, t_stack *stack, int *lookup)
{
    int i;

    if (!M || !stack || !lookup)  // Fix: aggiungi controlli null pointer
    {
        ft_printf("❌ Errore: puntatori nulli in create_matrix!\n");
        exit(1);
    }

    i = 0;
    while (i < stack->size_a)
    {
        ft_bzero(M[i], sizeof(int) * stack->size_a);
        matrix_operations += stack->size_a;
        i++;
    }
    write_matrix_ones(M, stack, lookup);
}

int **made_matrix(t_stack *stack)
{
    int **M;
    int *lookup;
    int k;

    if (!stack || stack->size_a <= 0)
        return (NULL);
    lookup = create_lookup_table(stack->sorted, stack->size_a);
    if (!lookup)
        return (NULL);
    M = malloc(stack->size_a * sizeof(int *));
    if (!M)
    {
        free(lookup);
        return (NULL);
    }
    k = 0;
    while (k < stack->size_a)
    {
        M[k] = malloc(stack->size_a * sizeof(int));
        if (!M[k])
        {
            while (--k >= 0)
                free(M[k]);
            free(M);
            free(lookup);
            return (NULL);
        }
        ft_bzero(M[k], stack->size_a * sizeof(int));
        matrix_operations += stack->size_a;
        k++;
    }
    create_matrix(M, stack, lookup);
    free(lookup);
    return (M);
}

void print_matrix(int **M, int size)
{
    int i;
    int j;

    if (!M || size <= 0)  // Fix: aggiungi controlli parametri
    {
        ft_printf("❌ Errore: parametri non validi in print_matrix!\n");
        return;
    }

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            ft_printf("%d ", M[i][j]);
            j++;
        }
        ft_printf("\n");
        i++;
    }
    ft_printf("Operazioni per la costruzione della matrice: %d\n", matrix_operations);
}
