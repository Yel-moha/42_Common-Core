#include "push_swap.h"

// Trova la posizione dell'elemento minimo in a
static int find_min_pos(t_stack *stack)
{
    int i = 1;
    int min = stack->a[0];
    int pos = 0;

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

// Ordina esattamente 3 elementi in a
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
    int i = 0;
    int best_pos = -1;
    int min_diff = 2147483647;
    int diff;

    while (i < stack->size_a)
    {
        diff = stack->a[i] - value;
        if (diff > 0 && diff < min_diff)
        {
            min_diff = diff;
            best_pos = i;
        }
        i++;
    }

    if (best_pos != -1)
        return best_pos;

    int max = stack->a[0];
    int max_pos = 0;
    i = 1;
    while (i < stack->size_a)
    {
        if (stack->a[i] > max)
        {
            max = stack->a[i];
            max_pos = i;
        }
        i++;
    }
    return ((max_pos + 1) % stack->size_a);
}

// Calcola il costo di rotazione
static int get_cost(int size, int pos)
{
    if (pos <= size / 2)
        return pos;
    else
        return (size - pos);
}

// Trova l'elemento ottimale in b da spostare in a
static int find_best_index(t_stack *stack)
{
    int i = 0;
    int best_index = 0;
    int min_cost = 2147483647;
    int cost_a, cost_b, pos_a;

    while (i < stack->size_b)
    {
        pos_a = target_position(stack, stack->b[i]);
        cost_a = get_cost(stack->size_a, pos_a);
        cost_b = get_cost(stack->size_b, i);

        if ((cost_a + cost_b < min_cost) ||
            (cost_a + cost_b == min_cost && cost_b < get_cost(stack->size_b, best_index)))
        {
            min_cost = cost_a + cost_b;
            best_index = i;
        }
        i++;
    }
    return (best_index);
}

// Porta un elemento in cima allo stack selezionato
static void bring_to_top(t_stack *stack, int pos, char stack_id)
{
    int count;

    if (stack_id == 'a')
    {
        if (pos <= stack->size_a / 2)
            while (pos-- > 0)
                ra(stack);
        else
        {
            count = stack->size_a - pos;
            while (count-- > 0)
                rra(stack);
        }
    }
    else if (stack_id == 'b')
    {
        if (pos <= stack->size_b / 2)
            while (pos-- > 0)
                rb(stack);
        else
        {
            count = stack->size_b - pos;
            while (count-- > 0)
                rrb(stack);
        }
    }
}

// Inserisce intelligentemente l'elemento migliore da b ad a
static void smart_insert(t_stack *stack)
{
    int best_b = find_best_index(stack);
    int pos_a = target_position(stack, stack->b[best_b]);

    bring_to_top(stack, best_b, 'b');
    bring_to_top(stack, pos_a, 'a');
    pa(stack);
}

// Ruota a fino alla posizione target
static void rotate_to_target(t_stack *stack, int pos)
{
    if (pos <= stack->size_a / 2)
        while (pos-- > 0)
            ra(stack);
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

    if (is_sorted(stack))
        return;

    while (stack->size_a > 3)
        pb(stack);

    if (stack->size_a == 3)
        sort_three(stack);

    while (stack->size_b > 0)
        smart_insert(stack);

    rotate_to_target(stack, find_min_pos(stack));
}
