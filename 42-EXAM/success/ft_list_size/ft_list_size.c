

// You must use the following structure in your program ft_list_size.c :

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

int	ft_list_size(t_list *begin_list)
{
    int i;

    i = 0;
    // while(begin_list->next != '\0') sbagliato perché next é un puntatore
    while(begin_list)
    {
        i++;
        begin_list = begin_list->next;
    }
    return (i);
}