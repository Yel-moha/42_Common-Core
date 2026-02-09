#include "philo.h"

long    get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long    get_timestamp_ms(long start_time)
{
    return(get_time_in_ms() - start_time);
}

int main(void) {
    long start = get_time_in_ms();
    
    printf("Inizio: %ld ms\n", start);
    
    sleep(2);  // Aspetta 2 secondi
    
    long now = get_timestamp_ms(start);
    
    printf("Ora: %ld ms\n", now);
    printf("Trascorsi: %ld ms (dovrebbero essere ~2000)\n", now);
    
    return 0;
}