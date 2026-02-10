#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	pthread_mutex_init(&data->end_mutex, NULL);
	data->meal_mutexes = malloc(sizeof(pthread_mutex_t) * data->philosophers_num);
	if (!data->meal_mutexes)
		return (0);
	i = 0;
	while (i < data->philosophers_num)
	{
		pthread_mutex_init(&data->meal_mutexes[i], NULL);
		i++;
	}
	return (1);
}

static void	cleanup(t_data *data, t_fork *forks, t_philosophers *philos)
{
	int	i;

	i = 0;
	while (i < data->philosophers_num)
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

static int	start_simulation(t_data *data)
{
	t_fork			*forks;
	t_philosophers	*philos;

	forks = take_forks(data);
	if (!forks)
		return (0);
	philos = malloc(sizeof(t_philosophers) * data->philosophers_num);
	if (!philos)
		return (free(forks), 0);
	data->start_time = get_time_in_ms();
	assign_to_philos(philos, data, forks);
	data->philosophers = philos;
	create_threads(philos, data);
	usleep(100);
	pthread_mutex_lock(&data->start_mutex);
	data->all_ready = 1;
	pthread_mutex_unlock(&data->start_mutex);
	monitor_and_join(philos, data);
	cleanup(data, forks, philos);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_input(ac, av))
		return (printf("Error: Invalid input\n"), 1);
	assign_data(ac, av, &data);
	data.all_ready = 0;
	data.ready_threads = 0;
	data.end_execution = 0;
	if (!init_mutexes(&data))
		return (printf("Error: Mutex init failed\n"), 1);
	if (!start_simulation(&data))
	{
		cleanup(&data, NULL, NULL);
		return (printf("Error: Simulation failed\n"), 1);
	}
	return (0);
}