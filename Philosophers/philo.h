#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

// Cercheremo in questo progetto affrontare la sincronizzazione di threads

typedef pthread_mutex_t t_mutex;
/*
    *struttura forchette (FORK)
*/

typedef struct s_fork
{
    t_mutex fork;
    int fork_id;
}       t_fork;


/*
    *struttura per i dati condivisi tra philosofi
*/

typedef struct s_data
{
    long philosophers_num;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long max_meals;  // [5] | flag opzionale
    bool start_execution;
    bool end_execution;
    long start_time;           // tempo di inizio simulazione (in ms)
    int ready_threads;
    int all_ready;
    pthread_mutex_t print_mutex;  // mutex per stampa sincronizzata
    pthread_mutex_t time_mutex;   // mutex per aggiornare/leggere last_meal_time
    pthread_mutex_t start_mutex;
    pthread_mutex_t end_mutex;
    t_philosophers  *philosophers;
}       t_data;


/*
    *struttura philosophers
    *esempio di esecuzione
        - ./philo 5 800 200 200 [5]
*/
typedef struct  s_philosopher
{
    int id;
    long meals_eaten;
    bool is_full;
    long last_time_meal; //tempo dell'ultimo pasto;
    t_fork  *left_fork;
    t_fork  *right_fork;
    pthread_t thread_id; // un filosofo e' un thread
    t_data      *data;
}   t_philosophers;


//  utils.c 
void    exit_error(const char *error);
long	ft_atol(const char *str);
int	check_philo_death(t_philosophers *philo, t_data *data);
void	print_death(t_philosophers *philo, t_data *data);


// assign.c
int     check_input(int ac, char **av);
void    assign_data(int ac, char **av, t_data *data);
t_fork  *take_forks(t_data data);
void    assign_to_philos(t_philosophers *philos, t_data *data, t_fork *forks);
void    create_threads(t_philosophers *philos, t_data *data);

// routine.c
long    get_time_in_ms(void);
long    get_timestamp_ms(long start_time);
void    print_state(t_philosophers *philo, char *state);
void    wait_for_start(t_data *data);
void    *philo_routine(void *arg);
void    *monitor_routine(void *arg);
#endif 