#include "philo.h"

void print_data(t_data *data)
{
    printf("num_philos = %d\n", data->num_philos);
    printf("time to die = %ld\n", data->time_to_die);
    printf("time to eat = %ld\n", data->time_to_eat);
    printf("time to sleep = %ld\n", data->time_to_sleep);
    printf("max meals = %ld\n", data->max_meals);
}