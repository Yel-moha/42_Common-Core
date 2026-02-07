#include "philo.h"

// qui raggrupperemo le funzioni di assegnazione.

static void* routine()
{
   for(int i = 0; i < 10000; i++)
   {
        //pthread_mutex_lock(&mutex);
        //mails++;
        //pthread_mutex_unlock(&mutex);
   }
}

void assign_to_philos(char **av, t_philosophers *philos, t_data *data)
{
    (void)philos;
    long i;
    long num_philos;

    num_philos = ft_atol(av[1]);
    data->philosophers_num = num_philos;
    pthread_t th[num_philos];
    i = 0;
        while(i < num_philos)
        {
            if(pthread_create(th + i, &routine, NULL, NULL) != 0)
                perror("Failed create thread\n");
            i++;
        }
        while(i >= 0)
        {
            i--;
            if(pthread_join(th[i], NULL) != 0)
                perror("Failed joining thread\n");
        }
}
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