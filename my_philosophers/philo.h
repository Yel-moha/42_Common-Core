#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

//forward declaration
typedef struct s_philos t_philos;

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
    pthread_mutex_t *meal_mutexes;
    t_philos        *philos;
} t_data;

//struttura filosofi
typedef struct s_philos
{
    int         id;
    long        meals_eaten;
    bool        is_full;
    long        last_time_meal;
    pthread_t   thread_id;
    t_data      *data;
    t_fork      *left_fork;
    t_fork      *right_fork;
}   t_philos;

//utils.c
long	ft_atol(const char *str);
void	cleanup(t_data *data, t_fork *forks, t_philos *philos);


//parse_and_simulate.c
int parse_input(int argc, char **argv);
void inizialize_data(t_data *data, int argc, char **argv);
int lets_simulate(t_data *data);
t_fork  *take_forks(t_data  *data);
void    forks_for_philos(t_fork *forks, t_data *data, t_philos *philos);

//time.c
long    get_time_in_millis(void);
long    get_timestamp(long start_time);
void    ft_usleep(t_data *data, long time);
void    update_last_meal(t_philos *philo);
long    get_last_meal_time(t_philos *philo);

//print.c
void    print(t_philos *philo, const char *state);
void    print_the_end(t_philos *philo, t_data *data);

//threads.c
int main(int argc, char **argv);
int	init_mutexes(t_data *data);
int philo_cycle(t_philos *philo);
void    *philo_routine(void *arg);
void    *philos_master(void *arg);

//routins.c
bool    check_the_end(t_data *data);
void    create_threads(t_philos *philos, t_data *data);
void    monitor_and_join(t_philos *philos, t_data *data);
void    wait_for_them(t_data *data);
int	try_take_forks(t_philos *philo);

//routine_helpers.c
void    release_forks(t_philos  *philo);
void    eat_action(t_philos *philo);
void    think_action(t_philos *philo);
void    sleep_action(t_philos *philo);
int     is_dead(t_philos *philo, t_data *data);

#endif