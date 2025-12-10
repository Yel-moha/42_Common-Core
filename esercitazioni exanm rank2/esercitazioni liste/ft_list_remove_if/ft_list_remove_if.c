#include "ft_list.h"
#include <stdlib.h>

void    ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    t_list  *cur;
    t_list  *prev;
    t_list  *tmp;

    if (!begin_list || !*begin_list)
        return;

    cur = *begin_list;
    prev = NULL;

    while (cur)
    {
        if ((*cmp)(cur->data, data_ref) == 0)
        {
            tmp = cur;
            if (prev == NULL)               // rimuove la testa della lista
                *begin_list = cur->next;
            else                            // rimuove un nodo in mezzo
                prev->next = cur->next;
            cur = cur->next;
            free(tmp);                      // libera il nodo
        }
        else
        {
            prev = cur;                     // avanza normalmente
            cur = cur->next;
        }
    }
}
