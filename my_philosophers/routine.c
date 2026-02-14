/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   routine.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yel-moha <yel-moha@student.42firenze.it	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/14 16:42:00 by yel-moha		  #+#	#+#			 */
/*   Updated: 2026/02/14 16:45:50 by yel-moha		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

bool	check_the_end(t_data *data)
{
	bool	end_it;

	pthread_mutex_lock(&data->end_mutex);
	end_it = data->end_exec;
	pthread_mutex_unlock(&data->end_mutex);
	return (end_it);
}

void	create_threads(t_philos *philos, t_data *data)
{
	long	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread_id, NULL,
				philo_routine, &philos[i]) != 0)
			perror("Failed create thread");
		i++;
	}
}

void	monitor_and_join(t_philos *philos, t_data *data)
{
	long		i;
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, philos_master, data) != 0)
		perror("Failed create monitor thread\n");
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			perror("Failed joining thread\n");
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		perror("Failed joining monitor thread\n");
}

void	wait_for_them(t_data *data)
{
	bool	all_exist;

	pthread_mutex_lock(&data->start_mutex);
	data->ready_threads++;
	pthread_mutex_unlock(&data->start_mutex);
	all_exist = false;
	while (!all_exist)
	{
		pthread_mutex_lock(&data->start_mutex);
		all_exist = data->we_all_exist;
		pthread_mutex_unlock(&data->start_mutex);
		if (!all_exist)
			usleep(100);
	}
}

int	try_take_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		print(philo, "has taken a fork");
		if (check_the_end(philo->data) || philo->data->num_philos == 1)
		{
			pthread_mutex_unlock(&philo->left_fork->fork);
			return (0);
		}
		pthread_mutex_lock(&philo->right_fork->fork);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		print(philo, "has taken a fork");
		if (check_the_end(philo->data) || philo->data->num_philos == 1)
		{
			pthread_mutex_unlock(&philo->right_fork->fork);
			return (0);
		}
		pthread_mutex_lock(&philo->left_fork->fork);
		print(philo, "has taken a fork");
	}
	return (1);
}
