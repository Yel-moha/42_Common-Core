#include "philo.h"

long    get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long    get_timestamp_ms(long start_time)
{
    return(get_time_in_ms() - start_time);
}

void print_state(t_philosophers *philo, char *state)
{
    long current_time;
    long timestamp;

    pthread_mutex_lock(&philo->data->print_mutex);
    current_time = get_time_in_ms();
    timestamp = current_time - philo->data->start_time;
    printf("%ld %d %s\n", timestamp, philo->id, state);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
void    wait_for_start(t_data *data)
{
    pthread_mutex_lock(&data->start_mutex);
    data->ready_threads++;
    pthread_mutex_unlock(&data->start_mutex);
    while(!data->all_ready)
        usleep(100);
}

void *philo_routine(void *arg)
{
    t_philosophers *philo;

    philo = (t_philosophers *) arg;
    wait_for_start(philo->data);
    if (philo->id % 2 == 0)
        usleep(100);
    while(!simulation_should_end(philo->data))
    {
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(&philo->left_fork->fork);
            print_state(philo, "has taken a fork");
            pthread_mutex_lock(&philo->right_fork->fork);
            print_state(philo, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(&philo->right_fork->fork);
            print_state(philo, "has taken a fork");
            pthread_mutex_lock(&philo->left_fork->fork);
            print_state(philo, "has taken a fork");
        }
        eat_action(philo);
        pthread_mutex_unlock(&philo->left_fork->fork);
        pthread_mutex_unlock(&philo->right_fork->fork);
        print_state(philo, "is sleeping");
        ft_usleep(philo->data->time_to_sleep);
        print_state(philo, "is thinking");
    }
    return (NULL);
}
void *monitor_routine(void *arg)
{
    t_data  *data;
    int i;

    data = (t_data *)arg;
    while(!check_simulation_end(data))
    {
        i = 0;
        while(i < data->philosophers_num)
        {
            if(check_philo_death(&data->philosophers[i], data))
                return (NULL);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}

