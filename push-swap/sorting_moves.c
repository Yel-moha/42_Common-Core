#include "push_swap.h"

int sort_from_matrix(t_stack *stack, int **M)
{
    int i;
    int target_pos;
    int num_moves;

    i = 0;
    num_moves = 0;
    while (i < stack->size_a)
    {
        target_pos = 0;
        while (target_pos < stack->size_a && M[i][target_pos] != 1)
            target_pos++;
        
        if (target_pos != i)
        {
            pb(stack);  // Metto temporaneamente l'elemento su B
            // Porto elemento in posizione target_pos in cima a A
            num_moves++;
            while (target_pos--)
            {
                ra(stack);
                num_moves++;
            }
            pa(stack); // Rimetto l'elemento nella posizione giusta
            num_moves++;
            // Ripristino ordine iniziale degli elementi sopra
            while (++target_pos < i)
            {
                rra(stack);
                num_moves++;
            }
        }
        else
        {
            ra(stack);  // Elemento già ordinato, passo avanti.
            num_moves++;
        }
            ra(stack);  // Elemento già ordinato, passo avanti.
            num_moves++;
        
        i++;
    }
    return (num_moves);
}
