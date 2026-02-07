#include "philo.h"

/*
    *./philo 5 800 200 200 [5]
*/

int main(int ac, char **av)
{
   //t_philosophers 
    if(ac == 5 || ac == 6)
    {
        
        t_philosophers *philos;
        long i;
        long num_philos;

        num_philos = ft_atol(av[1]);
        philos = malloc(sizeof(t_philosophers) * num_philos);
        i = 0;
        while(i < num_philos)
       {
        printf("ho assegnato l'id numero %ld \n", i);
        i++;
       }
        free(philos);
    }
    else
    {
        //Errore
        exit_error("Invalid input: \
        Correct one is like this: ./philo 5 800 200 200 [5]");
    }
    return 0;
}

