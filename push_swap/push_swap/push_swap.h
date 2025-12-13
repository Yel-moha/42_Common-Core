/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:33:40 by yel-moha          #+#    #+#             */
/*   Updated: 2025/12/13 17:33:41 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# include "ft_printf/libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdlib.h>

typedef struct s_stack
{
	int	*a;
	int	*b;
	int	size_a;
	int	size_b;
	int	size;
	int	*sorted;
	int	cost;
	int	moves;
	int	index;
	int	min;
	int	max;
}	t_stack;

typedef struct s_move
{
	int	index_b;
	int	cost_a;
	int	cost_b;
	int	total_cost;
}	t_move;

/* Input handling */
void	take_input(int argc, char **argv, t_stack *stack);
int		*inputs_array(int argc, char **argv);
int		check_input(char *argv);
void	init_stack(t_stack *stack, int argc);

/* Validations */
void	check_duplicates(t_stack *stack);
void	check_int_overflow(t_stack *stack);
int		is_sorted(t_stack *stack);

/* Sorting and array management */
int		*temp_order(t_stack *stack);
int		order_them(int *array, int size, int j, int i);
void	sort_array(int *a, int size, int *sorted);

/* Memory management */
void	free_all(t_stack *stack);

/* Basic operations */
void	sa(t_stack *stack);
void	sb(t_stack *stack);
void	ss(t_stack *stack);
void	pa(t_stack *stack);
void	pb(t_stack *stack);
void	ra(t_stack *stack);
void	rb(t_stack *stack);
void	rr(t_stack *stack);
void	rra(t_stack *stack);
void	rrb(t_stack *stack);
void	rrr(t_stack *stack);

/* Advanced operations */
void	normalize_stack(t_stack *stack);
void	cycle_sort(t_stack *stack);
void	bring_to_top(t_stack *stack, int pos, char id);
int		find_best_index(t_stack *stack);
int		get_cost(int size, int pos);
int		target_position(t_stack *stack, int value);
int		find_min_pos(t_stack *stack);
void	sort_three(t_stack *stack);

/* Helper functions */
int		find_closest_bigger(t_stack *stack, int value);
void	fill_normalized(int *temp, int *a, int size);
int		find_min_pos_index(t_stack *stack);
void	rotate_count(t_stack *stack, int count, void (*rotate_func)(t_stack *));

#endif
