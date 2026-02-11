/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:46:34 by yel-moha          #+#    #+#             */
/*   Updated: 2026/02/11 17:33:20 by yel-moha         ###   ########.fr       */
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