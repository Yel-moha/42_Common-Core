#include "philo.h"

int parse_input(int argc, char **argv)
{
    //aggiungere parsing is digit
    if(atol(argv[1]) < 1) // almeno 2 filosofi per evitare deadlock
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


int lets_simulate(t_data *data)
{
    t_fork      *forks;
    t_philos    *philos;

    forks = take_forks(data);
    if(!forks)
        return (0);
    philos = malloc(sizeof(t_philos) * data->num_philos);
    if(!philos)
    {
        free(forks);
        return (0);
    }
    data->start_time = get_time_in_millis();
    forks_for_philos(forks, data, philos);
    data->philos = philos;
    create_threads(philos, data);
    usleep(100);
    pthread_mutex_lock(&data->start_mutex);
    data->we_all_exist = true;
    pthread_mutex_unlock(&data->start_mutex);
    monitor_and_join(philos, data);
    cleanup(data, forks, philos);
    return (1);
}


t_fork  *take_forks(t_data  *data)
{
    t_fork      *forks;
    long i;

    forks = malloc(sizeof(t_fork) * data->num_philos);
    if(!forks)
        return (NULL);
    i = 0;
    while(i < data->num_philos)
    {
        pthread_mutex_init(&forks[i].fork, NULL);
        forks[i].id_fork = i;
        i++;
    }
    return (forks);
}

void    forks_for_philos(t_fork *forks, t_data *data, t_philos *philos)
{
    long    i;

    i = 0;
    while(i < data->num_philos)
    {
        philos[i].id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].is_full = false;
        philos[i].last_time_meal = data->start_time;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % data->num_philos];
        philos[i].data = data;
        i++;
    }
}
