#include "push_swap.h"

// Trova la posizione dell'elemento minimo in a
static int find_min_pos(t_stack *stack)
{
    int i;
    int min;
    int pos;

    i = 1;
    min = stack->a[0];
    pos = 0;
    while (i < stack->size_a)
    {
        if (stack->a[i] < min)
        {
            min = stack->a[i];
            pos = i;
        }
        i++;
    }
    return (pos);
}

// Trova la posizione migliore per inserire b[0] in a
static int target_position(t_stack *stack, int value)
{
    int i;
    int best_pos;
    int best_diff;

    i = 0;
    best_pos = -1;
    best_diff = 2147483647;
    while (i < stack->size_a)
    {
        if (stack->a[i] > value && (stack->a[i] - value) < best_diff)
        {
            best_diff = stack->a[i] - value;
            best_pos = i;
        }
        i++;
    }
    if (best_pos == -1)
        best_pos = find_min_pos(stack);
    return (best_pos);
}

// Ruota a fino alla posizione target
static void rotate_to_target(t_stack *stack, int pos)
{

    if (pos <= stack->size_a / 2)
    {
        while (pos-- > 0)
            ra(stack);
    }
    else
    {
        pos = stack->size_a - pos;
        while (pos-- > 0)
            rra(stack);
    }
}

// Ruota entrambi gli stack se possibile, altrimenti solo uno
static void rotate_both_to_target(t_stack *stack, int pos_a, int pos_b)
{
    while (pos_a > 0 && pos_b > 0)
    {
        rr(stack);
        pos_a--;
        pos_b--;
    }
    while (pos_a-- > 0)
        ra(stack);
    while (pos_b-- > 0)
        rb(stack);
}

// Ruota entrambi all'indietro se conviene
static void reverse_both_to_target(t_stack *stack, int pos_a, int pos_b)
{
    int rra_count = stack->size_a - pos_a;
    int rrb_count = stack->size_b - pos_b;

    while (rra_count > 0 && rrb_count > 0)
    {
        rrr(stack);
        rra_count--;
        rrb_count--;
    }
    while (rra_count-- > 0)
        rra(stack);
    while (rrb_count-- > 0)
        rrb(stack);
}

// Ordina 3 elementi in a (caso base)
static void sort_three(t_stack *stack)
{
    if (stack->a[0] > stack->a[1] && stack->a[1] < stack->a[2] && stack->a[0] < stack->a[2])
        sa(stack);
    else if (stack->a[0] > stack->a[1] && stack->a[1] > stack->a[2])
    {
        sa(stack);
        rra(stack);
    }
    else if (stack->a[0] > stack->a[1] && stack->a[1] < stack->a[2])
        ra(stack);
    else if (stack->a[0] < stack->a[1] && stack->a[1] > stack->a[2] && stack->a[0] < stack->a[2])
    {
        sa(stack);
        ra(stack);
    }
    else if (stack->a[0] < stack->a[1] && stack->a[1] > stack->a[2])
        rra(stack);
}

// Ottimizza i primi due elementi se necessario
static void maybe_swap_top(t_stack *stack)
{
    if (stack->size_a >= 2 && stack->a[0] > stack->a[1])
        sa(stack);
}

// Inserimento intelligente da b a a
static void smart_insert(t_stack *stack)
{
    int pos_a;
    int pos_b;


    pos_a = target_position(stack, stack->b[0]);
    pos_b = find_best_index(stack);

    if (pos_a == 0)
    {
        pa(stack);
        return;
    }
    if (pos_b > 0 && pos_a <= stack->size_a / 2 && pos_b <= stack->size_b / 2)
        rotate_both_to_target(stack, pos_a, pos_b);
    else if (pos_b > 0 && pos_a > stack->size_a / 2 && pos_b > stack->size_b / 2)
        reverse_both_to_target(stack, pos_a, pos_b);
    else
        rotate_to_target(stack, pos_a);
    pa(stack);
}

// Ordina lo stack a usando stack b come supporto
void cycle_sort(t_stack *stack)
{
    normalize_stack(stack);
    maybe_swap_top(stack);
    if(is_sorted(stack))
        return;
    while (stack->size_a > 3)
        pb(stack);
    sort_three(stack);
    while (stack->size_b > 0)
        smart_insert(stack);
    int final_pos = find_min_pos(stack);
    if (final_pos != 0)
        rotate_to_target(stack, final_pos);

  //  rotate_to_target(stack, find_min_pos(stack));
    ft_printf("Operazioni totali: %d\n", stack->moves);
}
