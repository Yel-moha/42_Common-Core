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
    int             we_all_exist;
    pthread_mutex_t print_mutex; //mutex per stampa sincronizzata
    pthread_mutex_t time_mutex;
    pthread_mutex_t end_mutex;
    pthread_mutex_t start_mutex;
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
int     lets_simulate(t_data *data);
t_fork  *take_forks(t_data  *data);
void    forks_for_philos(t_fork *forks, t_data *data, t_philos *philos);

//utils.c
long	ft_atol(const char *str);

//debug.c
void    print_data(t_data *data);

//time.c
long    get_time_in_millis(void);
long    get_timestamp(long start_time);
void    ft_usleep(t_data *data, long time);

//print.c
void    print(t_philos *philo, const char *state);

//routins.c
bool    check_the_end(t_data *data);
void    create_threads(t_philos *philos, t_data *data);
void    monitor_and_join(t_philos *philos, t_data *data);

#endif