/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   print.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yel-moha <yel-moha@student.42firenze.it	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/14 16:41:47 by yel-moha		  #+#	#+#			 */
/*   Updated: 2026/02/14 16:45:08 by yel-moha		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

void	print(t_philos *philo, const char *state)
{
	long	current_time;
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end_exec)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->end_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	current_time = get_time_in_millis();
	timestamp = current_time - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, state);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	print_the_end(t_philos *philo, t_data *data)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->end_mutex);
	if (philo->data->end_exec)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->end_mutex);
		return ;
	}
	data->end_exec = 1;
	pthread_mutex_unlock(&philo->data->end_mutex);
	printf("%ld %d died\n",
		get_time_in_millis() - data->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
