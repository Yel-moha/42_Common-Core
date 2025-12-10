#include <stdlib.h>

int     *ft_rrange(int start, int end)
{
    int *arr;
    int dim;
    int i;

    if(start > end)
        dim = 1 + (start - end);
    else
        dim = 1 + (end - start);
    arr = malloc(sizeof(int) * dim);
    if(!arr)
        return(NULL);
    i = dim - 1;
    arr[i] = start;
    while(i > 0)
    {
        if(start > end)
            arr[i - 1] = arr[i] - 1;
        else
            arr[i - 1] = arr[i] + 1;
        i--;
    }
    return (arr);
}