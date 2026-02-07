#include "philo.h"

/*
    *./philo 5 800 200 200 [5]
*/

int main(int ac, char **av)
{
    t_data  *data;
    if(!check_input(ac, av))
        exit_error("Invalid input: \
        Correct one is like this: ./philo 5 800 200 200 [5]");
    else if(parse_input(ac, av))
    {
        assign_data(ac, av, data);
    }
    if(ac == 5)
            // senza numero massimo di pasti
    if(ac == 6)
            // con un numero di pasti massimo
    return 0;
}

