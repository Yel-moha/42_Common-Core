#include "philo.h"

void print(t_philos *philo, const char *state)
{
    long current_time;
    long timestamp;

    pthread_mutex_lock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->data->end_mutex);
    if(philo->data->end_exec)
    {
        pthread_mutex_unlock(&philo->data->print_mutex);
        pthread_mutex_unlock(&philo->data->end_mutex);
        return ;
    }
    pthread_mutex_unlock(&philo->data->end_exec);
    current_time = get_time_in_millis();
    timestamp = current_time - philo->data->start_time;
    printf("%ld %d %s\n", timestamp, philo->id, state);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

