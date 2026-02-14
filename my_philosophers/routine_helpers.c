/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   routine_helpers.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yel-moha <yel-moha@student.42firenze.it	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/14 16:41:55 by yel-moha		  #+#	#+#			 */
/*   Updated: 2026/02/14 16:44:56 by yel-moha		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philos *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	eat_action(t_philos *philo)
{
	print(philo, "is eating");
	update_last_meal(philo);
	pthread_mutex_lock(&philo->data->meal_mutexes[philo->id - 1]);
	philo->meals_eaten++;
	if (philo->data->max_meals > 0
		&& philo->meals_eaten >= philo->data->max_meals)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->data->meal_mutexes[philo->id - 1]);
	ft_usleep(philo->data, philo->data->time_to_eat);
}

void	think_action(t_philos *philo)
{
	print(philo, "is thinking");
}

void	sleep_action(t_philos *philo)
{
	print(philo, "is sleeping");
	ft_usleep(philo->data, philo->data->time_to_sleep);
}

int	is_dead(t_philos *philo, t_data *data)
{
	long	last_meal;
	long	time_since_last_meal;

	last_meal = get_last_meal_time(philo);
	time_since_last_meal = get_time_in_millis() - last_meal;
	if (time_since_last_meal > data->time_to_die)
	{
		print_the_end(philo, data);
		pthread_mutex_lock(&data->end_mutex);
		data->end_exec = true;
		pthread_mutex_unlock(&data->end_mutex);
		return (1);
	}
	return (0);
}
