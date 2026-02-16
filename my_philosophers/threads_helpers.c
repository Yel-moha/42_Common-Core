/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   threads_helpers.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yel-moha <yel-moha@student.42firenze.it	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/14 16:42:06 by yel-moha		  #+#	#+#			 */
/*   Updated: 2026/02/14 16:45:39 by yel-moha		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

long	get_meals_eaten(t_philos *philo)
{
	long	meals;

	pthread_mutex_lock(&philo->data->meal_mutexes[philo->id - 1]);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->data->meal_mutexes[philo->id - 1]);
	return (meals);
}

int	all_philos_full(t_data *data)
{
	int		i;
	long	meals;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutexes[i]);
		meals = data->philos[i].meals_eaten;
		pthread_mutex_unlock(&data->meal_mutexes[i]);
		if (meals < data->max_meals)
			return (0);
		i++;
	}
	return (1);
}

int	check_deaths(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (is_dead(&data->philos[i], data))
		{
			pthread_mutex_lock(&data->end_mutex);
			data->end_exec = 1;
			pthread_mutex_unlock(&data->end_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	check_full_stop(t_data *data)
{
	check_deaths(data);
	if (data->max_meals > 0 && all_philos_full(data))
	{
		pthread_mutex_lock(&data->end_mutex);
		data->end_exec = 1;
		pthread_mutex_unlock(&data->end_mutex);
	}
}
