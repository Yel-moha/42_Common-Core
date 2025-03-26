#include "push_swap.h"

// Find the position of the minimum element in stack 'a'
static int find_min_pos(t_stack *stack)
{
    if (!stack || stack->size_a <= 0)
        return (-1);

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

// Sort exactly 3 elements in stack 'a'
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

// Find the best position to insert a value into stack 'a'
/* static int target_position(t_stack *stack, int value)
{
    if (!stack || stack->size_a <= 0)
        return -1;

    int i = 0;
    int best_pos = -1;
    int min_diff = INT_MAX;
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

    // If no valid position is found, return the position after the maximum element
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
 */

 static int target_position(t_stack *stack, int value)
{
    int i = 0;
    int pos = -1;
    int closest_bigger = INT_MAX;

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

    // Se nessuno è più grande, trova la posizione del numero più piccolo per inserire prima di esso
    int smallest = INT_MAX;
    int smallest_pos = 0;
    for (i = 0; i < stack->size_a; i++)
    {
        if (stack->a[i] < smallest)
        {
            smallest = stack->a[i];
            smallest_pos = i;
        }
    }
    return smallest_pos;
}

// Calculate the rotation cost
static int get_cost(int size, int pos)
{
    if (pos <= size / 2)
        return pos;
    else
        return (size - pos);
}

// Find the optimal element in stack 'b' to move to stack 'a'
static int find_best_index(t_stack *stack)
{
    if (!stack || stack->size_b <= 0)
        return -1;

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

// Bring an element to the top of the selected stack
static void bring_to_top(t_stack *stack, int pos, char stack_id)
{
    if (!stack || pos < 0)
        return;

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

// Smartly insert the best element from stack 'b' into stack 'a'
static void smart_insert(t_stack *stack)
{
    if (!stack || stack->size_b <= 0)
        return;

    int best_b = find_best_index(stack);
    int pos_a = target_position(stack, stack->b[best_b]);

    bring_to_top(stack, best_b, 'b');
    bring_to_top(stack, pos_a, 'a');
    pa(stack);
}

// Rotate stack 'a' to the target position
static void rotate_to_target(t_stack *stack, int pos)
{
    if (!stack || pos < 0)
        return;

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

// Sort stack 'a' using stack 'b' as support
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