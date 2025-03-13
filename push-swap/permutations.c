#include <stdlib.h>
#include <stdio.h>
#include "push_swap.h"

void init_matrix(int **M, int size)
{
    int i;
    int j;
    
    i= 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
            M[i][j++] = 0;
        i++;
    }
}

void find_permutation(int *a, int *sorted, int size, int **M)
{
    int i;
    int j;
    
    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            if (a[i] == sorted[j])
            {
                M[j][i] = 1;
                break;
            }
            j++;
        }
        i++;
    }
}

void apply_permutation(int **M, int *a, int *sorted, int size)
{
    int i;
    int j;
    
    i= 0;
    while (i < size)
    {
        sorted[i] = 0;
        j = 0;
        while (j < size)
            sorted[i] += M[i][j] * a[j++];
        i++;
    }
}

void sort_array(int *a, int size, int *sorted)
{
    int i;
    int j;
    int temp;

    i = 0;
    while (i < size)
        sorted[i++] = a[i - 1];
    i = 0;
    while (i < size - 1)
    {
        j = i + 1;
        while (j < size)
        {
            if (sorted[i] > sorted[j])
            {
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
            j++;
        }
        i++;
    }
}

void sort_using_matrix(int *a, int size, int *sorted)
{
    int **M;
    int i;
    
    i = 0;
    M = (int **)malloc(size * sizeof(int *));
    while (i < size)
        M[i++] = (int *)malloc(size * sizeof(int));

    init_matrix(M, size);
    sort_array(a, size, sorted);
    find_permutation(a, sorted, size, M);
    apply_permutation(M, a, sorted, size);

    i = 0;
    while (i < size)
        free(M[i++]);
    free(M);
}

/* int main()
{
    int a[] = {3, 1, 4, 2};
    int size = 4;
    int sorted[size];

    sort_using_matrix(a, size, sorted);

    int i = 0;
    while (i < size)
        printf("%d ", sorted[i++]);
    printf("\n");
    
    return 0;
}
 */