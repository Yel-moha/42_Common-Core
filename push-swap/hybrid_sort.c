#include "push_swap.h"

static int ft_max(int a, int b)
{
	return (a > b) ? a : b;
}

int max_a(t_stack *stack)
{
	int i;
	int max;

	i = 0;
	max = stack->a[0];
	while(i < stack->size_a)
	{
		if (stack->a[i] > max)
			max = stack->a[i];
		i++;
	}
	return max;
}

static int find_min_pos(t_stack *stack)
{
	int i;
	int min;
	int pos;

	if (!stack || stack->size_a <= 0)
		return -1;
	min = stack->a[0];
	pos = 0;
	for (i = 1; i < stack->size_a; i++)
	{
		if (stack->a[i] < min)
		{
			min = stack->a[i];
			pos = i;
		}
	}
	return pos;
}

static void sort_three(t_stack *stack)
{
	if (!stack || stack->size_a != 3)
		return ;
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

int get_cost_signed(t_stack *stack, int pos)
{
	int i;

	i = 0;
	while(i < stack->size_b)
	{
		if (stack->b[i] == stack->a[pos] + 1)
			pos = i;
		i++;
	}
	if (pos <= stack->size_a / 2)
		return pos;
	else
		return -(stack->size_b - pos);
}

int get_target_cost_a(t_stack *stack, int value)
{
	int i;
	int pos;
	int min_diff;
	int diff;

	pos = -1;
	min_diff = 2147483647;
	for (i = 0; i < stack->size_a; i++)
	{
		diff = stack->a[i] - value;
		if (diff > 0 && diff < min_diff)
		{
			min_diff = diff;
		//	pos = i;
			if (diff == 1)
			return get_cost_signed(stack, pos);
		}
	}
	if (pos == -1)
		pos = max_a(stack);
	return get_cost_signed(stack, pos);
}

static int find_best_index(t_stack *stack)
{
	int i;
	int best_index;
	int min_cost;
	int cost_a;
	int cost_b;
	int total_cost;

	best_index = 0;
	min_cost = 2147483647;
	for (i = 0; i < stack->size_b; i++)
	{
		cost_a = get_target_cost_a(stack, stack->b[i]);
		cost_b = get_cost_signed(stack, i);
		if ((cost_a >= 0 && cost_b >= 0) || (cost_a < 0 && cost_b < 0))
			total_cost = ft_max(abs(cost_a), abs(cost_b));
		else
			total_cost = abs(cost_a) + abs(cost_b);
		if (total_cost < min_cost)
		{
			min_cost = total_cost;
			best_index = i;
		}
	}
	return best_index;
}

static void smart_rotate(t_stack *stack, int cost_a, int cost_b)
{
	while (cost_a > 0 && cost_b > 0)
	{
		rr(stack);
		cost_a--;
		cost_b--;
	}
	while (cost_a < 0 && cost_b < 0)
	{
		rrr(stack);
		cost_a++;
		cost_b++;
	}
	while (cost_a > 0) { ra(stack); cost_a--; }
	while (cost_a < 0) { rra(stack); cost_a++; }
	while (cost_b > 0) { rb(stack); cost_b--; }
	while (cost_b < 0) { rrb(stack); cost_b++; }
}

static void smart_insert(t_stack *stack)
{
	if (!stack || stack->size_b <= 0)
		return;

	int best_b = find_best_index(stack);
	int cost_a = get_target_cost_a(stack, stack->b[best_b]);
	int cost_b = get_cost_signed(stack, best_b);

	smart_rotate(stack, cost_a, cost_b);
	pa(stack);
}

static void rotate_to_target(t_stack *stack, int pos)
{
	if (!stack || pos < 0)
		return;

	int cost = get_cost_signed(stack, pos);
	while (cost > 0) { ra(stack); cost--; }
	while (cost < 0) { rra(stack); cost++; }
}

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
