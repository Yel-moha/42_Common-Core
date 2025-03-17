#include "push_swap.h"

/* void free_all(t_stack *stack, int **M)
{
    int i;

    i = 0;
    if (M)
    {
        while (i < stack->size_a)
            free(M[i++]);
        free(M);
    }
    if (stack)
    {
        free(stack->a);
        free(stack->b);
        free(stack->sorted);
        free(stack);
    }
} */

void free_all(t_stack *stack, int **M)
{
    int i;

    if (stack->a)
        free(stack->a);
    if (stack->b)
        free(stack->b);
    if (stack->sorted)
        free(stack->sorted);
    i = 0;
    if (M)
    {
        while (i < stack->size_a)
        {
            if (M[i])
                free(M[i]);
            i++;
        }
        free(M);
    }
}


/* int main(int argc, char **argv)
{
    t_stack *stack;
    int **M;
    int num_moves;

    if (argc == 1)
        return (0);
    stack = malloc(sizeof(t_stack));
    if (!stack)
        exit(1);
    take_input(argc, argv, stack);
    if (!stack->a)
        return (free_all(stack, NULL), ft_putstr_fd("Error\n", 1), 1);
    check_duplicates(stack);
    stack->sorted = temp_order(stack);
    M = made_matrix(stack);
    print_matrix(M, stack->size_a);
    num_moves = sort_from_matrix(stack, M);
    ft_printf("Number of moves: %d\n", num_moves);
    free_all(stack, M);
    return (0);
}
 */

/*  #include "push_swap.h"

int main(int argc, char **argv)
{
    t_stack stack;
    int **M;

    if (argc < 2)
        return (0);
    take_input(argc, argv, &stack);
    stack.sorted = temp_order(&stack);
    stack.moves = 0;
    M = made_matrix(&stack);
    sort_from_cycles(&stack, M);
    ft_printf("Operazioni totali: %d\n", stack.moves);
    ft_printf("L'ordine finale è: ");
    for (int i = 0; i < stack.size_a; i++)
    {
        ft_printf("%d ", stack.sorted[i]);
    }
    print_matrix(M, stack.size_a);
    free_all(&stack, M);
    return (0);
}
 */

 #include "push_swap.h"

int main(int argc, char **argv)
{
    t_stack stack;
    int **M;

    if (argc < 2)
        return (0);

    ft_printf("🔍 Inizializzazione stack...\n");
    take_input(argc, argv, &stack);
    
    ft_printf("🔍 Costruzione matrice...\n");
    M = made_matrix(&stack);
    
    if (!M)
    {
        ft_printf("❌ Errore: matrice non allocata!\n");
        return (1);
    }

    ft_printf("✅ Matrice costruita. Stampiamo:\n");
    print_matrix(M, stack.size_a);

    ft_printf("✅ Ordinamento in corso...\n");
    sort_from_cycles(&stack, M);
    
    ft_printf("✅ Ordinamento completato!\n");

    free_all(&stack, M);
    return (0);
}


// test 100 numeri
/* ./push_swap 132 76 297 610 197 261 715 763 90 931 637 343 855 864 666 267 395 211 657 933 994 888 800 
731 185 225 410 184 129 86 3 149 947 696 899 670 584 445 472 820 196 256 944 122 799 480 253 709 394 975 
714 753 678 644 276 531 821 405 889 742 868 504 590 273 912 870 535 153 999 856 43 908 499 845 155 295 552
 989 367 850 279 53 511 227 916 455 752 222 138 577 609 578 660 773 751 25 205 553 770 199

*/