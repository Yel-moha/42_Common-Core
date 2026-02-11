#include "philo.h"

int main(int argc, char **argv)
{
    t_data *data;

    if(argc != 5 && argc != 6)
    {
        perror("Invalid input\n");
        //return 1;
    }
    if(!parse_input(argc, argv))
        perror("Number < 0 not allowed on this simulation\n");
    data = malloc(sizeof(t_data) * 1);
    inizialize_data(data, argc, argv);
    print_data(data);
    free(data);
    return 0;
}

