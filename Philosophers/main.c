#include "philo.h"

/*
    *./philo 5 800 200 200 [5]
*/

int main(int ac, char **av)
{
    if(ac == 5 || ac == 6)
    {
        //il numero di input e' corretto
    }
    else
    {
        //Errore
        exit_error("Invalid input:");
        exit_error("Correct one is like this: ./philo 5 800 200 200 [5]");
    }
}