#include "philo.h"
// riprendere il canale youtube sui threads dall numero 6 intitolato get a return from a thread
/*
void* routine()
{
    printf("Test from threads\n");
    sleep(3);
    printf("Ending thread\n");
}
*/

int mails = 0;
pthread_mutex_t mutex;

void* routine()
{
   for(int i = 0; i < 10000; i++)
   {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
   }
}
int main(int argc, char **argv)
{
    pthread_t th[4];
    int i;

    pthread_mutex_init(&mutex, NULL);
    for(i = 0; i < 200; i++)
    {
        if(pthread_create(th + i, NULL, &routine, NULL) != 0)
        {
            perror("Failed create thread\n");
            return 1;
        }
        printf("Thread %d is started: \n", i);
    }
    for(i = 0; i < 200; i++)
    {
        if(pthread_join(th[i], NULL) != 0)
            return 2;
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("il numero di mail e' %d\n", mails);
    return 0;
}

/*

void* routine()
{
   for(int i = 0; i < 10000; i++)
        mails++;
    printf("il numero di mail e' %d\n", mails);
}

int main(int argc, char **argv)
{
    pthread_t t1, t2;
    //int mails = 0;
    
    if(pthread_create(&t1, NULL, &routine, NULL) != 0)
        return 1;
    if(pthread_create(&t2, NULL, &routine, NULL) != 0)
       return 3;
    if(pthread_join(t1, NULL) != 0)
        return 2;
    if(pthread_join(t2, NULL) != 0)
       return 4;
    return 0;
}


usando questa funzione e chiamandola come argomento di due thread diversi nel main come t1 e t2 
succede che nel frattempo che il primo thread incrementa la variabile mails localmente, (ovvero
all'interno del ciclo for nella funzione) essendo appunto i due thread paralleli, anche il secondo
thread tenta di fare lo stesso, infatti il risultato non e' 20000 come ci si aspetta besi un numero 
bensi un numero spesso minore di 20000 ma compreso tra 10000 e 20000 il che suggerisce la velocita
del ramo del processo/processore dedicato al singolo thread

*/