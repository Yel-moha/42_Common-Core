#include "push_swap.h"
#include <stdlib.h>

static int matrix_operations = 0;  // Contatore globale delle operazioni

// Crea una tabella di lookup per trovare velocemente la posizione di ogni numero in sorted[]
static int *create_lookup_table(int *sorted, int size)
{
    int *lookup;
    int i;

    if (!sorted)
    {
        ft_printf("❌ Errore: `sorted` è NULL in `create_lookup_table()`!\n");
        exit(1);
    }

    lookup = malloc(sizeof(int) * 1000); // 🔧 Usa un array più grande per mappare numeri grandi
    if (!lookup)
        exit(1);

    // Inizializza lookup con valori fuori dai limiti
    i = 0;
    while (i < 1000)  // 🔧 Settiamo tutto a -1 per evitare errori di accesso
    {
        lookup[i] = -1;
        i++;
    }

    // Riempire lookup con indici normalizzati
    i = 0;
    while (i < size)
    {
        lookup[sorted[i]] = i; // 🔧 Mappa i numeri reali a un intervallo da 0 a size-1
        i++;
    }
    return (lookup);
}



/* static void write_matrix_ones(int **M, t_stack *stack, int *lookup)
{
    int i;
    int index;

    if (!M || !stack || !lookup || stack->size_a <= 0)
        exit(1);

    i = 0;
    while (i < stack->size_a)
    {
        if (stack->a[i] < 0 || stack->a[i] >= stack->size_a)
            exit(1);
            
        index = lookup[stack->a[i]];
        
        if (index < 0 || index >= stack->size_a)
            exit(1);
        
        M[i][index] = 1;
        matrix_operations++;
        i++;
    }
}
 */

 static void write_matrix_ones(int **M, t_stack *stack, int *lookup)
{
    int i;
    int index;

    i = 0;
    while (i < stack->size_a)
    {
        if (stack->a[i] < 0 || stack->a[i] >= 1000) // 🔧 Controllo input
        {
            ft_printf("❌ Errore: stack->a[%d] = %d fuori dai limiti!\n", i, stack->a[i]);
            exit(1);
        }

        index = lookup[stack->a[i]];
        if (index == -1) // 🔧 Verifica se il numero esiste in `lookup[]`
        {
            ft_printf("❌ Errore: lookup[%d] non trovato!\n", stack->a[i]);
            exit(1);
        }

        M[i][index] = 1; // 🟢 Ora l'operazione è sicura
        i++;
    }
}


// Inizializza la matrice e la riempie con le permutazioni
static void create_matrix(int **M, t_stack *stack, int *lookup)
{
    int i;

    i = 0;
    while (i < stack->size_a)
    {
        ft_bzero(M[i], sizeof(int) * stack->size_a);
        matrix_operations += stack->size_a;  // Conta la pulizia della riga
        i++;
    }
    write_matrix_ones(M, stack, lookup);
}

// Alloca la matrice dinamicamente e la riempie
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
// Stampa la matrice per debug e il numero di operazioni usate
void print_matrix(int **M, int size)
{
    int i;
    int j;

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
