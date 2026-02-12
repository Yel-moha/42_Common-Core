/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:46:34 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/12 12:27:21 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_in_millis(void)
{
    struct  timeval tv;
    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long get_timestamp(long start_time)
{
    return(get_time_in_millis() - start_time);
}

void    ft_usleep(t_data *data, long time)
{
    long    start;

    start = get_time_in_millis();
    while(!check_the_end(data))
    {
        if(get_time_in_millis() - start >= time)
            break ;
        usleep(100);
    }
}

void    update_last_meal(t_philos *philo)
{
    pthread_mutex_lock(&philo->data->meal_mutexes[philo->id - 1]);
    philo->last_time_meal = get_time_in_millis();
    pthread_mutex_unlock(&philo->data->meal_mutexes[philo->id - 1]);
}

long    get_last_meal_time(t_philos *philo)
{
    long    last_meal;
    pthread_mutex_lock(&philo->data->meal_mutexes[philo->id - 1]);
    last_meal = philo->last_time_meal;
    pthread_mutex_unlock(&philo->data->meal_mutexes[philo->id - 1]);
    return (last_meal);
}