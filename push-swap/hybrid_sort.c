#include "push_swap.h"

// Trova la posizione dell’elemento minimo in A
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
    return pos;
}

static int find_min_pos_b(t_stack *stack)
{
    int i = 1;
    int min = stack->b[0];
    int pos = 0;

    while (i < stack->size_b)
    {
        if (stack->b[i] < min)
        {
            min = stack->b[i];
            pos = i;
        }
        i++;
    }
    return pos;
}


// Ordina 3 elementi in A (caso base)
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

// Calcola il costo di rotazione fino alla posizione `pos`
static int get_cost(int size, int pos)
{
    if (pos <= size / 2)
        return pos;
    return size - pos;
}

// Trova la posizione ottimale in A dove inserire `value`
static int target_position(t_stack *stack, int value)
{
    int i;
    int pos = -1;
    int min = INT_MAX;
    int max = INT_MIN;
   // int min_pos = 0;

    for (i = 0; i < stack->size_a; i++)
    {
        if (stack->a[i] == value + 1)
        {
              ft_printf(" il successivo di value = %d sono io stack->a[%d] = %d, all'indice %d\n", value, i, stack->a[i], i);
              pos = i;
              return (pos);
              break ;
        }
            
        if (stack->a[i] < min )
        {
            min = stack->a[i];
           // min_pos = i;
          //  if(stack->a[i] == value + 1)
              //  ft_printf(" il successivo sono io stack->a[%d] = %d, all'indice %d\n", i, stack->a[i], i);
        }
        if (stack->a[i] > max)
            max = stack->a[i];
    }

    // Se non ci sono elementi più grandi, value è il massimo e va prima del minimo
   // if (pos == -1)
    //    return min_pos;

    return pos;
}


// Porta una posizione in cima allo stack specificato
static void bring_to_top(t_stack *stack, int pos, char stack_id)
{
    int size = (stack_id == 'a') ? stack->size_a : stack->size_b;
    void (*rotate)(t_stack *) = (stack_id == 'a') ? ra : rb;
    void (*reverse)(t_stack *) = (stack_id == 'a') ? rra : rrb;

    if (pos <= size / 2)
        while (pos-- > 0)
            rotate(stack);
    else
        while ((size - pos++) > 0)
            reverse(stack);
}

// Trova il miglior indice in B da spostare in A
static int find_best_index(t_stack *stack)
{
    int best_index = 0;
    int min_cost = INT_MAX;
    int pos_min_b;
    int cost_b;
    
    pos_min_b = find_min_pos_b(stack);
    for (int i = 0; i < stack->size_b; i++)
    {
        int pos_a = target_position(stack, stack->b[i]);
        if(pos_a != -1 && i == 0)
        {
            cost_b = 0;
            best_index = 0;
            //break ;
        }
        else if( pos_a != -1 && i > 0)
        {
            //break ;
          // cost_b = get_cost(stack->size_b, i);
           pos_a = target_position(stack, stack->b[i]);
           best_index = i;
           cost_b = get_cost(stack->size_b, i);
        }
        else if(pos_a == -1)
        {
            cost_b = get_cost(stack->size_b, pos_min_b);
            pos_a = target_position(stack, stack->b[pos_min_b]);
        }
        int cost_a = get_cost(stack->size_a, pos_a);
        int total = cost_a + cost_b;

        if (total < min_cost) //(total < min_cost)
        {
            if(total == 1)
            {
                best_index = i;
                min_cost = total;
                ft_printf("qui \n");
                ft_printf(" stack->b[%d] = %d e il suo costo è %d\n", i, stack->b[i], cost_b);
                ft_printf(" stack->a[%d] = %d e il suo costo é %d\n", i, stack->a[pos_a], cost_a);
                ft_printf(" target position restistuisce %d cost_a = %d, cost_b = %d\n", pos_a, cost_a, cost_b);
                ft_printf("qui \n");
                return best_index;

            }

        }
    }
    return best_index;
}

// Inserisce in modo intelligente da B ad A
static void smart_insert(t_stack *stack)
{
    int best_b = find_best_index(stack);
    int pos_a = target_position(stack, stack->b[best_b]);

    bring_to_top(stack, best_b, 'b');

    // Check: se last(A) è il predecessore diretto di first(A), anticipa rotazione
    if (stack->size_a >= 1)
    {
        int first = stack->a[0];
        int last = stack->a[stack->size_a - 1];
        if ((last + 1 == first) || (last == stack->max && first == stack->min))
            ra(stack);
    }

    bring_to_top(stack, pos_a, 'a');
    pa(stack);

    // Swap se inserito fuori posto
    int next_pos = (target_position(stack, stack->a[0]) + 1) % stack->size_a;
    if (stack->size_a >= 2 && stack->a[0] > stack->a[1] && next_pos != 1)
        sa(stack);
}

// Rotazione finale per mettere il minimo in cima
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

// Funzione principale di ordinamento (cycle sort)
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
