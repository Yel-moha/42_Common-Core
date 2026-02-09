#include "philo.h"

// qui raggrupperemo le funzioni di assegnazione.

int check_input(int ac, char **av)
{
    int i;

    if(ac == 5 || ac == 6)
    {
        i = 1;
        while(i < ac - 1)
        {
            if(ft_atol(av[i]) < 0)
                return 0;
            i++;
        }
    }
    else
        return 0;
    return 1;
}

void assign_data(int ac, char **av, t_data *data)
{
    data->philosophers_num = ft_atol(av[1]);
    data->time_to_die = ft_atol(av[2]);
    data->time_to_eat = ft_atol(av[3]);
    data->time_to_sleep = ft_atol(av[4]);
    if(ac == 6)
        data->max_meals = ft_atol(av[5]);
    else
        data->max_meals = -1;
}

t_fork *take_forks(t_data data)
{
    t_fork *forks;
    long i;

    forks = malloc(sizeof(t_fork) * data.philosophers_num);
    if(!forks)
        return NULL;
    while(i < data.philosophers_num)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    return forks;
}
void assign_to_philos(t_philosophers *philos, t_data *data, t_fork *forks)
{
    long i;
    long num_philos;

    num_philos = data->philosophers_num;
    i = 0;
    while(i < num_philos)
    {
        philos[i].id = i + 1;
        philos->meals_eaten = 0;
        philos->is_full = false;
        philos[i].last_time_meal = 0;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % num_philos];
        philos->data = data;
        i++;
    }
}
void    create_threads(t_philosophers *philos, t_data *data)
{
    long i;
    long num_philos;

    num_philos = data->philosophers_num;
    i = 0;
    while(i < num_philos)
    {
        if(pthread_create(&philos[i].thread_id, NULL, &routine, &philos[i]) != 0)
            perror("Failed create thread\n");
        i++;
    }
    i = 0;
    while(i < num_philos)
    {
        if(pthread_join(philos[i].thread_id, NULL) != 0)
            perror("Failed joining thread\n");
        i++;
    }
}