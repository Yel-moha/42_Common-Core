#include "push_swap.h"

// Trova la posizione dell'elemento minimo nello stack A
static int find_min_pos(t_stack *stack)
{
    if (!stack || stack->size_a <= 0)
        return -1;

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
    return pos;
}

// Ordina esattamente 3 elementi nello stack A
static void sort_three(t_stack *stack)
{
    if (!stack || stack->size_a != 3)
        return;

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

// Trova la posizione ideale per inserire un valore in A
static int target_position(t_stack *stack, int value)
{
    int i = 0;
    int pos = -1;
    int closest_bigger = INT_MAX;

    // Cerca il valore immediatamente più grande di `value`
    while (i < stack->size_a)
    {
        if (stack->a[i] > value && stack->a[i] < closest_bigger)
        {
            closest_bigger = stack->a[i];
            pos = i;
        }
        i++;
    }

    if (pos != -1)
        return pos;

    // Se il valore è il massimo, va dopo il più grande in A
    int largest = INT_MIN;
    int largest_pos = 0;
    for (i = 0; i < stack->size_a; i++)
    {
        if (stack->a[i] > largest)
        {
            largest = stack->a[i];
            largest_pos = i;
        }
    }

    return (largest_pos + 1) % stack->size_a;
}

// Calcola il costo della rotazione
static int get_cost(int size, int pos)
{
    if (pos <= size / 2)
        return pos;
    return (size - pos);
}

// Trova il miglior indice in B da pushare in A
static int find_best_index(t_stack *stack)
{
    int i = 0;
    int best_index = 0;
    int min_cost = INT_MAX;
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
    return best_index;
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

// Inserisce in modo intelligente il miglior elemento da B ad A
static void smart_insert(t_stack *stack)
{
    if (!stack || stack->size_b <= 0)
        return;

    int best_b = find_best_index(stack);
    int pos_a = target_position(stack, stack->b[best_b]);

    bring_to_top(stack, best_b, 'b');

    // Controlla se l'ultimo elemento di A è il predecessore del primo
    if (stack->size_a >= 1)
    {
        int first = stack->a[0];
        int last = stack->a[stack->size_a - 1];
        if (last + 1 == first || (last == stack->max && first == stack->min)) // opzionale wrap-around
            ra(stack); // metti il successore dopo il suo predecessore
    }

    bring_to_top(stack, pos_a, 'a');
    pa(stack);

    // Se l’elemento inserito è maggiore di quello successivo, potrebbe servire uno swap
    int next_pos = (target_position(stack, stack->a[0]) + 1) % stack->size_a;
    if (stack->size_a >= 2 && stack->a[0] > stack->a[1] && next_pos != 1)
        sa(stack);
}

// Ruota A per mettere il minimo in cima
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

// Algoritmo principale: cycle sort con ottimizzazioni
void cycle_sort(t_stack *stack)
{
    if (!stack)
        return;

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
