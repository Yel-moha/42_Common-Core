/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:47:51 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/14 16:48:03 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc != 5 && argc != 6) || !parse_input(argc, argv))
		return (printf("Error: Invalid input\n"), 1);
	inizialize_data(&data, argc, argv);
	data.we_all_exist = false;
	data.ready_threads = 0;
	data.end_exec = 0;
	if (!init_mutexes(&data))
		return (printf("Error: Mutex init failed\n"), 1);
	if (!lets_simulate(&data))
	{
		cleanup(&data, NULL, NULL);
		return (printf("Error: Simulation failed\n"), 1);
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	pthread_mutex_init(&data->end_mutex, NULL);
	data->meal_mutexes = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->meal_mutexes)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->meal_mutexes[i], NULL);
		i++;
	}
	return (1);
}

int	philo_cycle(t_philos *philo)
{
	if (!try_take_forks(philo))
		return (0);
	if (check_the_end(philo->data))
	{
		release_forks(philo);
		return (0);
	}
	eat_action(philo);
	release_forks(philo);
	sleep_action(philo);
	think_action(philo);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philos	*philo;
	long		meals;

	philo = (t_philos *)arg;
	wait_for_them(philo->data);
	if (philo->id % 2 == 0)
		usleep(100);
	while (!check_the_end(philo->data))
	{
		if (!philo_cycle(philo))
			break ;
		meals = get_meals_eaten(philo);
		if (philo->data->max_meals > 0
			&& meals >= philo->data->max_meals)
			break ;
	}
	return (NULL);
}

void	*philos_master(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!check_the_end(data))
	{
		if (check_deaths(data))
			break ;
		check_full_stop(data);
		usleep(1000);
	}
	return (NULL);
}
