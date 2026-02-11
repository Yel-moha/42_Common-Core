#include "philo.h"

int main(int argc, char **argv)
{
    if(argc != 5 && argc != 6)
    {
        perror("Invalid input\n");
        //return 1;
    }
    if(!parse_input(argc, argv))
        perror("Number < 0 not allowed on this simulation\n");
    t_data *data;
    inizialize_data(data, argc, argv);
    print_data(data);
    return 0;
}