#ifndef PHILO
#define PHILO

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//lista per i data condivisi tra filosofi

typedef struct s_data
{
    int     num_philos;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    max_meals;
} t_data;

// parsing.c
int     parse_input(int argc, char **argv);
void    inizialize_data(t_data *data, int argc, char **argv);

//utils.c
long	ft_atol(const char *str);

//debug.c
void print_data(t_data *data);

#endif