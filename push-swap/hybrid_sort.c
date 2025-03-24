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


// Trova la posizione migliore per inserire un valore in a
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

static int get_cost(int size, int pos)
{
    if (pos <= size / 2)
        return pos;
    return size - pos;
}

/* static void do_rotations(t_stack *stack, int pos_a, int pos_b)
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
 
static void do_reverse_rotations(t_stack *stack, int pos_a, int pos_b)
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
        */

// Trova il miglior elemento da spostare da b ad a
static int find_best_index(t_stack *stack)
{
    int i;
    int best_index;
    int min_cost;
    int cost_a;
    int cost_b;
    int pos_a;

    i = 0;
    best_index = 0;
    min_cost = 2147483647;
    while (i < stack->size_b)
    {
        pos_a = target_position(stack, stack->b[i]);
        cost_a = get_cost(stack->size_a, pos_a);
        cost_b = get_cost(stack->size_b, i);
        if (cost_a + cost_b < min_cost)
        {
            min_cost = cost_a + cost_b;
            best_index = i;
        }
        i++;
    }
    return (best_index);
}

static void bring_to_top(t_stack *stack, int pos, char stack_id)
{
    if (stack_id == 'a')
    {
        if (pos <= stack->size_a / 2)
            while (pos-- > 0)
                ra(stack);
        else
            while ((stack->size_a - pos++) > 0)
                rra(stack);
    }
    else if (stack_id == 'b')
    {
        if (pos <= stack->size_b / 2)
            while (pos-- > 0)
                rb(stack);
        else
            while ((stack->size_b - pos++) > 0)
                rrb(stack);
    }
}

// Inserimento intelligente da b a a
static void smart_insert(t_stack *stack)
{
    int best_b;
    int pos_a;

    best_b = find_best_index(stack);
    pos_a = target_position(stack, stack->b[best_b]);

    bring_to_top(stack, best_b, 'b');
    bring_to_top(stack, pos_a, 'a');
    pa(stack);
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
// Ordina lo stack a usando stack b come supporto
void cycle_sort(t_stack *stack)
{
    normalize_stack(stack);
    while (stack->size_a > 3)
        pb(stack);
    if (stack->size_a == 3)
        sort_three(stack);
    while (stack->size_b > 0)
        smart_insert(stack);
    rotate_to_target(stack, find_min_pos(stack));
    ft_printf("Operazioni totali: %d\n", stack->moves);
}
