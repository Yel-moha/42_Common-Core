#include "philo.h"

int parse_input(int argc, char **argv)
{
    if(atol(argv[1]) < 0)
        return (0);
    if(atol(argv[2]) < 0)
        return (0);
    if(atol(argv[3]) < 0)
        return (0);
    if(atol(argv[4]) < 0)
        return (0);
    if(argc == 6)
        if(atol(argv[5]) < 0)
            return (0);
    return (1);
}

void inizialize_data(t_data *data, int argc, char **argv)
{
    data->num_philos = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
    if(argc == 6)
        data->max_meals = ft_atol(argv[5]);
    else
        data->max_meals = -1;
}