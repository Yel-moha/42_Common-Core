#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "ft_printf/libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdlib.h>

// Struttura principale per gestire le pile
typedef struct s_stack
{
    int *a;
    int *b;
    int size_a;
    int size_b;
    int size;
    int *sorted;
    int moves;
} t_stack;

// Input Handling
void    take_input(int argc, char **argv, t_stack *stack);
//int     *inputs_array(int argc, char **argv);
int *inputs_array(int argc, char **argv, t_stack *stack);
int     check_input(char *argv);
void init_stack(t_stack *stack, int argc);


// Validazioni
void    check_duplicates(t_stack *stack);
void    check_int_overflow(t_stack *stack);

// Ordinamento e gestione array
int     *temp_order(t_stack *stack);
int     order_them(int *array, int size, int j, int i);
void    sort_array(int *a, int size, int *sorted);

// Gestione matrice
//void    init_matrix(int **M, int size);
//void    apply_permutation(int **M, int *a, int *sorted, int size);
//void    find_permutation(int *a, int *sorted, int size, int **M);
//void    sort_using_matrix(int *a, int size, int *sorted);
//int sort_from_matrix(t_stack *stack, int **M);

// Funzioni di stampa (debug)
//void    print_matrix(int **M, int size);

// Gestione memoria
void    free_all(t_stack *stack, int **M);

// Operazioni di base
void    sa(t_stack *stack);
void    sb(t_stack *stack);
void    ss(t_stack *stack);
void    pa(t_stack *stack);
void    pb(t_stack *stack);
void    ra(t_stack *stack);
void    rb(t_stack *stack);
void    rr(t_stack *stack);
void    rra(t_stack *stack);
void    rrb(t_stack *stack);
void    rrr(t_stack *stack);

// chunk_sort.c
void    sort_chunk(t_stack *stack, int chunks);
void    move_back_to_a(t_stack *stack);
void    chunk_sort(t_stack *stack);

// math_sort.c
void sort_from_cycles(t_stack *stack, int **M);

// matrix_utils.c
// matrix_utils.c
int **made_matrix(t_stack *stack);
void print_matrix(int **M, int size);

// matrix_utils_2.c
//int *create_lookup_table(int *sorted, int size);



#endif