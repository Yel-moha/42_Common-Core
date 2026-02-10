#include "philo.h"

void    update_last_meal(t_philosophers *philo)
{
    pthread_mutex_lock(&philo->data->meal_mutexes[philo->id - 1]);
    philo->last_time_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->data->meal_mutexes[philo->id - 1]);
}
long    get_last_meal_time(t_philosophers *philo)
{
    long    last_meal;
    pthread_mutex_lock(&philo->data->meal_mutexes[philo->id - 1]);
    last_meal = philo->last_time_meal;
    pthread_mutex_unlock(&philo->data->meal_mutexes[philo->id - 1]);
    return (last_meal);
}

void    eat_action(t_philosophers *philo)
{
    print_state(philo, "is eating");
    update_last_meal(philo);
    philo->meals_eaten++;
    ft_usleep(philo->data, philo->data->time_to_eat);
}

void    think_action(t_philosophers *philo)
{
    print_state(philo, "is thinking");
}

void    sleep_action(t_philosophers *philo)
{
    print_state(philo, "is sleeping");
    ft_usleep(philo->data, philo->data->time_to_sleep);
}

bool    simulation_should_end(t_data *data)
{
    bool ended;

    pthread_mutex_lock(&data->end_mutex);
    ended = data->end_execution;
    pthread_mutex_unlock(&data->end_mutex);
    return (ended);
}

bool    check_simulation_end(t_data *data)
{
    bool ended;

    pthread_mutex_lock(&data->end_mutex);
    ended = data->end_execution;
    pthread_mutex_unlock(&data->end_mutex);
    return (ended);
}

void    ft_usleep(t_data *data, long time)
{
    long start;

    start = get_time_in_ms();
    while (!simulation_should_end(data))
    {
        if (get_time_in_ms() - start >= time)
            break ;
        usleep(100);
    }
}