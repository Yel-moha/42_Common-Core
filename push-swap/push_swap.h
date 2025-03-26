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
    int **M;
    int cost;
    int moves;
    int index;
} t_stack;

// Input Handling
void    take_input(int argc, char **argv, t_stack *stack);
//int     *inputs_array(int argc, char **argv);
int *inputs_array(int argc, char **argv);
int     check_input(char *argv);
void init_stack(t_stack *stack, int argc);


// Validazioni
void    check_duplicates(t_stack *stack);
void    check_int_overflow(t_stack *stack);
int is_sorted(t_stack *stack);

// Ordinamento e gestione array
int     *temp_order(t_stack *stack);
int     order_them(int *array, int size, int j, int i);
void    sort_array(int *a, int size, int *sorted);

// Gestione memoria
void    free_all(t_stack *stack);

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

// Operazioni avanzate
void    radix_sort(t_stack *stack);
void    normalize_stack(t_stack *stack);

void cycle_sort(t_stack *stack);




#endif

#ifdef DEBUG
ft_printf("Operazioni totali: %d\n", stack->moves);
#endif
