#include "push_swap.h"

// Trova la posizione dell'elemento minimo nello stack 'a'
static int find_min_pos(t_stack *stack)
{
	int i;
	int min;
	int pos;

	if (!stack || stack->size_a <= 0)
		return (-1);
	min = stack->a[0];
	pos = 0;
	i = 1;
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

// Ordina esattamente 3 elementi in stack 'a'
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

// Trova la posizione corretta in cui inserire un valore nello stack 'a'
static int target_position(t_stack *stack, int value)
{
	int i;
	int pos;
	int closest_bigger;
	int largest;
	int largest_pos;

	i = 0;
	pos = -1;
	closest_bigger = INT_MAX;
	while (i < stack->size_a)
	{
		if((stack->a[i] == value + 1) && (stack->size_b == 1))
			return (i);		
		//pos = i;
			//if(stack->a[i] == value - 1)
				//pos = i;
		
	}
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
		return (pos);
	// Se nessun numero nello stack 'a' è più grande, trova il più grande
	largest = INT_MIN;
	largest_pos = 0;
	i = 0;
	while (i < stack->size_a)
	{
		if (stack->a[i] > largest)
		{
			largest = stack->a[i];
			largest_pos = i;
		}
		i++;
	}
	return ((largest_pos + 1) % stack->size_a);
}

// Calcola il numero minimo di rotazioni necessarie
static int get_cost(int size, int pos)
{
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

// Trova l'indice del miglior elemento in 'b' da inserire in 'a'
static int find_best_index(t_stack *stack)
{
	int i;                  // Contatore per iterare attraverso lo stack b
	int best_index;         // Indice del miglior elemento trovato
	int min_cost;          // Costo minimo totale trovato finora
	int cost_a;            // Costo per portare l'elemento nella posizione corretta in a
	int cost_b;            // Costo per portare l'elemento in cima allo stack b
	int pos_a;             // Posizione target nello stack a

	if (!stack || stack->size_b <= 0)  // Controllo validità dello stack
		return (-1);
	i = 0;                             // Inizializzazione del contatore
	best_index = 0;                    // Inizializzazione dell'indice migliore
	min_cost = INT_MAX;                // Inizializzazione del costo minimo al massimo valore possibile
	while (i < stack->size_b)          // Itera attraverso tutti gli elementi dello stack b
	{
		pos_a = target_position(stack, stack->b[i]);  // Trova la posizione target in a
		cost_a = get_cost(stack->size_a, pos_a);      // Calcola il costo per stack a
		cost_b = get_cost(stack->size_b, i);          // Calcola il costo per stack b
		// Se il costo totale è minore del minimo trovato
		if ((cost_a + cost_b < min_cost) || \
		(cost_a + cost_b == min_cost && cost_b < get_cost(stack->size_b, best_index)))  // O se è uguale ma con costo b minore
		{
			min_cost = cost_a + cost_b;               // Aggiorna il costo minimo
			best_index = i;                           // Aggiorna l'indice migliore
		}
		i++;                                          // Incrementa il contatore
	}
	return (best_index);                             // Ritorna l'indice del miglior elemento trovato
}
// Porta l'elemento alla cima dello stack selezionato
static void bring_to_top(t_stack *stack, int pos, char stack_id)
{
	int count;

	if (!stack || pos < 0)
		return ;
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

// Inserisce in modo intelligente il miglior elemento da 'b' in 'a'
static void smart_insert(t_stack *stack)
{
	int best_b;
	int pos_a;

	if (!stack || stack->size_b <= 0)
		return ;
	best_b = find_best_index(stack);
	pos_a = target_position(stack, stack->b[best_b]);
   // pos_a = 0;
	bring_to_top(stack, best_b, 'b');
	bring_to_top(stack, pos_a, 'a');
	pa(stack);
}

// Ruota lo stack 'a' fino a portare il minimo in cima
static void rotate_to_target(t_stack *stack, int pos)
{
	if (!stack || pos < 0)
		return ;
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

// Funzione principale: esegue cycle sort con stack 'b' come supporto
void cycle_sort(t_stack *stack)
{
	if (!stack)
		return ;
	normalize_stack(stack);
   /*. /////////////////////////////////////debug////////////////
    int i = 0;
    while (i < stack->size_a)
    {
        ft_printf("%d ", stack->a[i]);
        i++;
    }
    /////////////////////////////////////////////////////*/
	if (is_sorted(stack))
		return ;
	while (stack->size_a > 3)
		pb(stack);
	if (stack->size_a == 3)
		sort_three(stack);
	while (stack->size_b > 0)
		smart_insert(stack);
	rotate_to_target(stack, find_min_pos(stack));
}
