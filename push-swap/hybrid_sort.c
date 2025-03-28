#include "push_swap.h"
//#include <limits.h>

static int ft_max(int a, int b)
{
	return (a > b) ? a : b;
}


// Trova la posizione del valore minimo nello stack A
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

// Ordina esattamente 3 elementi in stack A
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

// Calcola il costo con segno per portare la posizione in cima allo stack
int get_cost_signed(int size, int pos)
{
	if (pos <= size / 2)
		return pos; // rotazione normale
	else
		return -(size - pos); // reverse rotazione
}

// Calcola il costo (con segno) per portare A nella posizione giusta per inserire `value`
int get_target_cost_a(t_stack *stack, int value)
{
	int i;
	int pos = -1;
	int min_diff = INT_MAX;

	// Cerca il primo numero maggiore di value
	for (i = 0; i < stack->size_a; i++)
	{
		int diff = stack->a[i] - value;
		if (diff > 0 && diff < min_diff)
		{
			min_diff = diff;
			pos = i;
		}
	}

	// Se trovato un valore maggiore, ritorna il costo per arrivarci
	if (pos != -1)
		return get_cost_signed(stack->size_a, pos);

	// Altrimenti, value è il massimo → va dopo il minimo
	int min = INT_MAX;
	for (i = 0; i < stack->size_a; i++)
	{
		if (stack->a[i] < min)
		{
			min = stack->a[i];
			pos = i;
		}
	}
	if (pos == -1)
	{
		ft_printf("⚠️ Errore: target_position fallita per value = %d\n", value);
		return 0;
	}
	return get_cost_signed(stack->size_a, pos);
}

// Trova l’indice dell’elemento in B con minor costo totale di inserimento
static int find_best_index(t_stack *stack)
{
	int i;
	int best_index = 0;
	int min_cost = INT_MAX;

	for (i = 0; i < stack->size_b; i++)
	{
		int cost_a = get_target_cost_a(stack, stack->b[i]);
		int cost_b = get_cost_signed(stack->size_b, i);
		int total_cost;

		// Se possono essere combinati (stessa direzione), il costo è max
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

// Ruota entrambi gli stack in modo ottimale (usa rr / rrr se possibile)
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

// Inserisce l’elemento ottimale da B in A con movimenti minimi
static void smart_insert(t_stack *stack)
{
	if (!stack || stack->size_b <= 0)
		return;

	int best_b = find_best_index(stack);
	int cost_a = get_target_cost_a(stack, stack->b[best_b]);
	int cost_b = get_cost_signed(stack->size_b, best_b);

	smart_rotate(stack, cost_a, cost_b);
	pa(stack);
}

// Porta il minimo in cima ad A alla fine dell’ordinamento
static void rotate_to_target(t_stack *stack, int pos)
{
	if (!stack || pos < 0)
		return;

	int cost = get_cost_signed(stack->size_a, pos);
	while (cost > 0) { ra(stack); cost--; }
	while (cost < 0) { rra(stack); cost++; }
}

// Funzione principale dell'algoritmo
void cycle_sort(t_stack *stack)
{
	if (!stack)
		return;

	normalize_stack(stack);
	if (is_sorted(stack))
		return;

	// Sposta tutti tranne 3 elementi da A a B
	while (stack->size_a > 3)
		pb(stack);

	// Ordina i 3 elementi rimasti
	if (stack->size_a == 3)
		sort_three(stack);

	// Inserisci in A gli elementi da B in ordine corretto
	while (stack->size_b > 0)
		smart_insert(stack);

	// Porta il minimo in cima per concludere l'ordinamento
	rotate_to_target(stack, find_min_pos(stack));
}
