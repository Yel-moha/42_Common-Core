#include "push_swap.h"

static int find_min_pos(t_stack *stack)
{
    int i;
    int min;
    int pos;

    if (!stack || stack->size_a <= 0)
        return (-1);
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

static void sort_three(t_stack *stack)
{
    int a;
    int b;
    int c;

    if (!stack || stack->size_a != 3)
        return ;
    a = stack->a[0];
    b = stack->a[1];
    c = stack->a[2];
    if (a > b && b < c && a < c)
        sa(stack);
    else if (a > b && b > c)
    {
        sa(stack);
        rra(stack);
    }
    else if (a > b && b < c)
        ra(stack);
    else if (a < b && b > c && a < c)
    {
        sa(stack);
        ra(stack);
    }
    else if (a < b && b > c)
        rra(stack);
}

static int binary_search(int *arr, int size, int value)
{
    int left;
    int right;
    int mid;

    left = 0;
    right = size - 1;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] == value)
            return (mid);
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return (left);
}

static int target_position(t_stack *stack, int value)
{
    if (value < stack->sorted[0])
        return (0);
    if (value > stack->sorted[stack->size_a - 1])
        return (0);
    return (binary_search(stack->sorted, stack->size_a, value));
}

static int get_cost(int size, int pos)
{
    if (pos <= size / 2)
        return (pos);
    return (size - pos);
}

static int find_best_index(t_stack *stack)
{
    int i;
    int best_index;
    int min_cost;
    int current_cost;

    i = 0;
    best_index = 0;
    min_cost = INT_MAX;
    while (i < stack->size_b)
    {
        current_cost = get_cost(stack->size_a, target_position(stack, stack->b[i])) 
                     + get_cost(stack->size_b, i);
        if (current_cost < min_cost)
        {
            min_cost = current_cost;
            best_index = i;
        }
        i++;
    }
    return (best_index);
}

static void rotate_both(t_stack *stack, int *pos_a, int *pos_b)
{
    while (*pos_a > 0 && *pos_b > 0 && *pos_a <= stack->size_a / 2 && *pos_b <= stack->size_b / 2)
    {
        rr(stack);
        (*pos_a)--;
        (*pos_b)--;
    }
}

static void reverse_rotate_both(t_stack *stack, int *pos_a, int *pos_b)
{
    while (*pos_a > stack->size_a / 2 && *pos_b > stack->size_b / 2 
           && *pos_a < stack->size_a && *pos_b < stack->size_b)
    {
        rrr(stack);
        (*pos_a)++;
        (*pos_b)++;
    }
}

static void bring_to_top_optimized(t_stack *stack, int pos_a, int pos_b)
{
    rotate_both(stack, &pos_a, &pos_b);
    reverse_rotate_both(stack, &pos_a, &pos_b);
    while (pos_a > 0 && pos_a <= stack->size_a / 2)
    {
        ra(stack);
        pos_a--;
    }
    while (pos_b > 0 && pos_b <= stack->size_b / 2)
    {
        rb(stack);
        pos_b--;
    }
    while (pos_a > stack->size_a / 2 && pos_a < stack->size_a)
    {
        rra(stack);
        pos_a++;
    }
    while (pos_b > stack->size_b / 2 && pos_b < stack->size_b)
    {
        rrb(stack);
        pos_b++;
    }
}

static void smart_insert(t_stack *stack)
{
    int best_b;
    int pos_a;

    if (!stack || stack->size_b <= 0)
        return ;
    best_b = find_best_index(stack);
    pos_a = target_position(stack, stack->b[best_b]);
    bring_to_top_optimized(stack, pos_a, best_b);
    pa(stack);
    if (stack->size_a >= 2 && stack->a[0] > stack->a[1])
        sa(stack);
}

static void rotate_to_target(t_stack *stack)
{
    int min_pos;
    int cost;

    min_pos = find_min_pos(stack);
    if (min_pos == 0)
        return ;
    cost = get_cost(stack->size_a, min_pos);
    if (cost > stack->size_a / 2)
    {
        cost = stack->size_a - cost;
        while (cost-- > 0)
            rra(stack);
    }
    else
    {
        while (cost-- > 0)
            ra(stack);
    }
}

void cycle_sort(t_stack *stack)
{
    if (!stack || is_sorted(stack))
        return ;
    while (stack->size_a > 3)
    {
        if (stack->a[0] != stack->max && stack->a[0] != stack->min)
            pb(stack);
        else
            ra(stack);
    }
    if (stack->size_a == 3)
        sort_three(stack);
    while (stack->size_b > 0)
        smart_insert(stack);
    rotate_to_target(stack);
}