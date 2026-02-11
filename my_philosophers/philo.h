#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

typedef pthread_mutex_t t_mutex;

//struttura forchette
typedef struct s_fork
{
    t_mutex fork;
    int     id_fork;
} t_fork;

//lista per i data condivisi tra filosofi

typedef struct s_data
{
    int             num_philos;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    long            max_meals;
    bool            start_exec; // flag booleano avvio esecuzione
    bool            end_exec;   //flag booleano fine esecuzione (la morte di un filosofo)
    long            start_time; // tempo inizio esecuzione dei thread;
    int             ready_threads;
    pthread_mutex_t print_state; //mutex per stampa sincronizzata
    pthread_mutex_t time_mutex;
    t_philos        *philos;
} t_data;

//struttura filosofi
typedef struct s_philos
{
    int         id;
    long        meals_eaten;
    bool        is_full;
    long        last_time_meal;
    pthread_t   *thread_id;
    t_data      *data;
    t_fork      *left_fork;
    t_fork      *right_fork;
}   t_philos;


// parsing.c
int     parse_input(int argc, char **argv);
void    inizialize_data(t_data *data, int argc, char **argv);
t_fork  *take_forks(t_data  *data);
void    forks_for_philos(t_fork *forks, t_data *data, t_philos *philos);

//utils.c
long	ft_atol(const char *str);

//debug.c
void    print_data(t_data *data);

//time.c
long    get_time_in_millis(void);
long    get_timestamp(long start_time);

#endif