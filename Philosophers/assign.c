#include "philo.h"

// qui raggrupperemo le funzioni di assegnazione.

void assign_to_philos(int ac, char **av, t_philosophers *philos)
{
    long i;
    long num_philos;

    num_philos = ft_atol(av[1]);
    i = 0;
        while(i < num_philos)
        {
            philos->id = i;
            i++;
        }
}