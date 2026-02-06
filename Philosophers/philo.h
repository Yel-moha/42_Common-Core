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
    *struttura philosophers
    *esempio di esecuzione
        - ./philo 5 800 200 200 [5]
*/
typedef struct  s_philosopher
{
    int id;
    long conuter_mels;
    bool is_full;
    long last_time_meal; //tempo dell'ultimo pasto;
    t_fork  *left_fork;
    t_fork  *right_fork;
    pthread_t thread_id; // un filosofo e' un thread
    t_data      *data;
}   t_philosophers;


/*
    *struttura per i dati condivisi tra philosofi
*/

typedef struct s_data
{
    long philosophers_num;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long max_meals;  // [5] | flaf opzionale
    bool start_execution;
    bool end_execution;;
}       t_data;

//  utils.c 
void exit_error(const char *error);

#endif 