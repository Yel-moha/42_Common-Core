/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yel-moha <yel-moha@student.42firenze.it	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/14 16:42:24 by yel-moha		  #+#	#+#			 */
/*   Updated: 2026/02/14 16:45:08 by yel-moha		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	num;
	int		sign;

	sign = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = ((str[i] - 48) + (num * 10));
		i++;
	}
	if (!ft_isdigit(str[i]) && str[i])
		return (-1);
	return (num * sign);
}

void	cleanup(t_data *data, t_fork *forks, t_philos *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->meal_mutexes[i]);
		pthread_mutex_destroy(&forks[i].fork);
		i++;
	}
	free(data->meal_mutexes);
	free(forks);
	free(philos);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->time_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	pthread_mutex_destroy(&data->end_mutex);
}
