#include "philo.h"

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
    int num = atoi(argv[1]);
    pthread_t th[num];
    int i;

    pthread_mutex_init(&mutex, NULL);
    for(i = 0; i < num; i++)
    {
        if(pthread_create(th + i, NULL, &routine, NULL) != 0)
        {
            perror("Failed create thread\n");
            return 1;
        }
        printf("Thread %d is started: \n", i);
    }
    for(i = 0; i < num; i++)
    {
        if(pthread_join(th[i], NULL) != 0)
            return 2;
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("il numero di mail e' %d\n", mails);
    return 0;
}
