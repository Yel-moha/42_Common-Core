#include "list.h"

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    t_list *swap;
    int temp;

    swap = lst;
    while(lst && lst->next)
    {
        if(!cmp(lst->data, lst->next->data))
        {
            temp = lst->data;
            lst->data = lst->next->data;
            lst->next->data = temp;
            lst = swap;
        }
        else
          lst = lst->next;
    }
    return swap;
}
