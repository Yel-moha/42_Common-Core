#include "philo.h"

void exit_error(const char *error)
{
    printf("%s\n", error);
    //exit(EXIT_FAILURE);
}

long	ft_atol(const char *str)
{
	int	i;
	long	num;
	int	sign;

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
	return (num * sign);
}

int	check_philo_death(t_philosophers *philo, t_data *data)
{
	long	time_since_meal;
	long	last_meal;

	last_meal = get_last_meal_time(philo);
	time_since_meal = get_time_in_ms() - last_meal;
	if(time_since_meal > data->time_to_die)
	{
		print_death(philo, data);
		return (1);
	}
	return (0);
}

void	print_death(t_philosophers *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_execution)
	{
		pthread_mutex_unlock(&data->end_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	data->end_execution = 1;
	pthread_mutex_unlock(&data->end_mutex);
	printf("%ld %d died\n", 
		get_time_in_ms() - data->start_time, 
		philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}