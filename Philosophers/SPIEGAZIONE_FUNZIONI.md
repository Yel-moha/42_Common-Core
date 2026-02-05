# Spiegazione Dettagliata - Funzioni Progetto Filosofi

---

## 📖 PARTE 1: TEORIA DEI THREAD

### Cosa sono i Thread?

Un **thread** è un "filo di esecuzione" all'interno di un programma. A differenza dei processi:
- **Processo**: Programma completo con memoria isolata (pesante, lento)
- **Thread**: Esecuzione parallela dentro lo STESSO processo (leggero, veloce)

#### Caratteristiche dei Thread:
- **Condividono memoria**: Tutti i thread dello stesso processo vedono le stesse variabili globali
- **Esecuzione parallela**: Su multi-core, girano veramente in parallelo; su single-core, il sistema operativo cambia velocemente tra loro
- **Concorrenza**: Molti thread possono accedere alle stesse risorse contemporaneamente
- **Necessitano sincronizzazione**: Se accedono alle stesse variabili, possono creare **race condition** (problemi di coerenza dati)

#### Esempio concettuale:
```
PROCESSO UNICO
│
├─ Thread 1: Legge dati
├─ Thread 2: Elabora dati
├─ Thread 3: Scrive risultati
│
└─ Memoria condivisa: Variabili globali accessibili da tutti
```

#### Problema della Concorrenza:
```c
// Variabile globale
int counter = 0;

// Thread 1                    // Thread 2
void *thread1() {              void *thread2() {
    counter++;                     counter++;
}                              }

// Se entrambi leggono 0, incrementano a 1, e scrivono 1
// Risultato atteso: counter = 2
// Risultato reale: counter = 1 (RACE CONDITION!)
```

Questo è il motivo dei **MUTEX** - per proteggere le variabili condivise.

---

## 🔧 PARTE 2: FUNZIONI DETTAGLIATE

---

## **1. MEMSET**

### Prototipo:
```c
#include <string.h>
void *memset(void *s, int c, size_t n);
```

### Parametri:
- `s` (void *): Puntatore al blocco di memoria da riempire
- `c` (int): Valore con cui riempire (convertito a unsigned char)
- `n` (size_t): Numero di byte da riempire

### Ritorno:
- Ritorna il puntatore `s` stesso

### Spiegazione:
Riempie `n` byte consecutivi di memoria partendo dall'indirizzo `s` con il valore `c`. Utile per inizializzare memoria a 0 o a un valore specifico.

### Esempi di Applicazione:

```c
// Esempio 1: Azzerare una struttura
typedef struct s_data {
    int number;
    char name[50];
} t_data;

t_data my_data;
memset(&my_data, 0, sizeof(my_data));
// Ora tutti i campi di my_data sono 0

// Esempio 2: Azzerare un array
int array[100];
memset(array, 0, sizeof(int) * 100);
// Tutto l'array è pieno di 0

// Esempio 3: Riempire con valore specifico
char buffer[10];
memset(buffer, 'A', 10);
// buffer contiene: AAAAAAAAAA

// Esempio 4: Nel progetto Filosofi
typedef struct s_philosopher {
    int id;
    int times_eaten;
    long long last_meal_time;
} t_philosopher;

t_philosopher philo;
memset(&philo, 0, sizeof(philo));
// Tutti i campi inizializzati a 0
```

### Utilità:
- **Inizializzazione sicura**: Garantisce che i dati non contengono "spazzatura"
- **Prevenzione di bug**: Evita comportamenti imprevisti da valori non inizializzati
- **Efficienza**: Molto veloce, implementato a livello di sistema

---

## **2. MALLOC**

### Prototipo:
```c
#include <stdlib.h>
void *malloc(size_t size);
```

### Parametri:
- `size` (size_t): Numero di byte da allocare

### Ritorno:
- Puntatore all'inizio del blocco di memoria allocato
- `NULL` se l'allocazione fallisce

### Spiegazione:
Alloca dinamicamente `size` byte nello heap (memoria a disposizione del programma). A differenza degli array normali (stack), la memoria allocata con malloc persiste fino a quando non la liberi.

### Esempi di Applicazione:

```c
// Esempio 1: Allocare un singolo intero
int *number = malloc(sizeof(int));
if (!number) {
    perror("malloc");
    return (1);
}
*number = 42;
printf("Valore: %d\n", *number);
free(number);

// Esempio 2: Allocare un array
int num_elements = 100;
int *array = malloc(sizeof(int) * num_elements);
if (!array)
    return (1);
for (int i = 0; i < num_elements; i++)
    array[i] = i;
free(array);

// Esempio 3: Allocare una struttura
struct s_philosopher {
    int id;
    char name[50];
};

struct s_philosopher *philo = malloc(sizeof(struct s_philosopher));
if (!philo)
    return (1);
philo->id = 1;
strcpy(philo->name, "Socrates");
free(philo);

// Esempio 4: Allocare array di strutture (IMPORTANTE PER FILOSOFI)
int number_of_philosophers = 5;
t_philosopher *philosophers = malloc(sizeof(t_philosopher) * number_of_philosophers);
if (!philosophers)
    return (1);

for (int i = 0; i < number_of_philosophers; i++) {
    philosophers[i].id = i;
    philosophers[i].times_eaten = 0;
}

free(philosophers);
```

### Utilità:
- **Memoria dinamica**: Alloca memoria in base al runtime, non al compile-time
- **Flessibilità**: Puoi allocare quello che ti serve al momento
- **Vita prolungata**: Persiste fino a free()
- **CRITICO**: Controllare SEMPRE se ritorna NULL

---

## **3. FREE**

### Prototipo:
```c
#include <stdlib.h>
void free(void *ptr);
```

### Parametri:
- `ptr` (void *): Puntatore alla memoria allocata con malloc (o calloc, realloc)

### Ritorno:
- Nessun ritorno (void)

### Spiegazione:
Libera il blocco di memoria precedentemente allocato con malloc. Dopo free(), il puntatore diventa invalido e accedervi è undefined behavior. Buona pratica: assegnare NULL al puntatore dopo free().

### Esempi di Applicazione:

```c
// Esempio 1: Free singolo elemento
int *num = malloc(sizeof(int));
free(num);
num = NULL;  // Buona pratica

// Esempio 2: Free array
int *array = malloc(sizeof(int) * 100);
free(array);
array = NULL;

// Esempio 3: Cleanup completo (IMPORTANTE PER FILOSOFI)
typedef struct s_data {
    pthread_mutex_t *fork_locks;
    t_philosopher *philosophers;
} t_data;

void cleanup(t_data *data, int num_philosophers) {
    // Distruggere mutex prima di free
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&data->fork_locks[i]);
    }
    
    // Liberare memoria
    free(data->fork_locks);
    free(data->philosophers);
    data->fork_locks = NULL;
    data->philosophers = NULL;
}

// Esempio 4: Nel main
int main() {
    int n = 5;
    t_philosopher *philos = malloc(sizeof(t_philosopher) * n);
    
    if (!philos)
        return (1);
    
    // ... usa philos ...
    
    free(philos);  // Sempre liberare prima di uscire
    philos = NULL;
    return (0);
}
```

### Utilità:
- **Prevenire memory leak**: Memoria non liberata si accumula
- **Pulizia risorse**: Importante per programmi lunghi (il tuo progetto!)
- **Garbage collection manuale**: C non ha GC automatico

---

## **4. PRINTF**

### Prototipo:
```c
#include <stdio.h>
int printf(const char *format, ...);
```

### Parametri:
- `format` (const char *): Stringa di formato con %x, %d, %s, ecc.
- `...` (variadic): Argomenti variabili che corrispondono ai placeholder

### Ritorno:
- Numero di caratteri stampati (o -1 se errore)

### Spiegazione:
Stampa testo formattato a stdout. Molto utile per debug e output. Nel progetto Filosofi, printf deve essere **sincronizzato con mutex** per evitare output intrecciato tra thread.

### Placeholder comuni:
- `%d` - intero (int)
- `%ld` - long
- `%lld` - long long
- `%s` - stringa (char *)
- `%c` - carattere (char)
- `%x` - esadecimale
- `%f` - float/double

### Esempi di Applicazione:

```c
// Esempio 1: Output semplice
printf("Hello World\n");

// Esempio 2: Con variabili
int age = 25;
char name[] = "Marco";
printf("Nome: %s, Età: %d\n", name, age);
// Output: Nome: Marco, Età: 25

// Esempio 3: Con timestamp (CRITICO PER FILOSOFI)
long long time_ms = 1500;
int philo_id = 2;
printf("%lld ms: Philosopher %d is eating\n", time_ms, philo_id);
// Output: 1500 ms: Philosopher 2 is eating

// Esempio 4: CON MUTEX (THREAD-SAFE)
pthread_mutex_t print_lock;

void safe_print(const char *format, long long time, int id, const char *action) {
    pthread_mutex_lock(&print_lock);
    printf("%lld ms: Philosopher %d %s\n", time, id, action);
    pthread_mutex_unlock(&print_lock);
}

// Nel thread:
safe_print("%lld ms: Philosopher %d %s\n", get_time(), philo->id, "is eating");

// Esempio 5: Formato con padding (per output pulito)
printf("%-5d %-20s %10lld\n", id, name, timestamp);
// - = allineamento a sinistra
// 5 = minimo 5 caratteri
```

### Utilità:
- **Output diagnostico**: Vedere cosa fa il programma
- **Debugging**: Tracciare l'esecuzione
- **Obbligatorio per Filosofi**: Output di timestamp e azioni

---

## **5. WRITE**

### Prototipo:
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```

### Parametri:
- `fd` (int): File descriptor (0=stdin, 1=stdout, 2=stderr)
- `buf` (const void *): Buffer con i dati da scrivere
- `count` (size_t): Numero di byte da scrivere

### Ritorno:
- Numero di byte scritti (può essere < count)
- -1 se errore

### Spiegazione:
Scrive `count` byte dal buffer `buf` al file descriptor `fd`. Più "basso livello" di printf, quindi più thread-safe in alcuni contesti. In C, printf internamente usa write.

### Esempi di Applicazione:

```c
// Esempio 1: Scrivere su stdout
write(1, "Hello\n", 6);

// Esempio 2: Scrivere su stderr
write(2, "Error!\n", 7);

// Esempio 3: Scrivere da un buffer
char buffer[100];
snprintf(buffer, 100, "%d %s\n", 42, "test");
write(1, buffer, strlen(buffer));

// Esempio 4: Nel progetto Filosofi (alternativa a printf)
char msg[100];
long long time_ms = 1500;
int philo_id = 2;

int len = snprintf(msg, 100, "%lld ms: Philosopher %d is eating\n", time_ms, philo_id);
write(1, msg, len);

// Esempio 5: Gestione parziale
ssize_t bytes_written = write(1, "Test", 4);
if (bytes_written != 4) {
    perror("write");
    // Solo 4 byte sono stati scritti, o c'è stato un errore
}
```

### Utilità:
- **Basso livello**: Direttamente al file descriptor
- **Thread-safe**: write() è atomica, a differenza di printf
- **Efficiente**: Niente buffering come printf
- **Controllo**: Sai esattamente quanti byte sono stati scritti

---

## **6. USLEEP**

### Prototipo:
```c
#include <unistd.h>
int usleep(useconds_t usec);
```

### Parametri:
- `usec` (useconds_t): Microsecondi (1 ms = 1000 μs)

### Ritorno:
- 0 se successo
- -1 se interrotto da segnale

### Spiegazione:
Pausa l'esecuzione del thread corrente per il numero di microsecondi specificato. Utile per simulare il tempo di lavoro (mangiare, dormire) nel progetto Filosofi.

### Conversioni:
```
1 microsecondo (μs)  = 0.000001 secondi
1 millisecondo (ms)  = 0.001 secondi = 1000 μs
1 secondo (s)        = 1000 ms = 1,000,000 μs
```

### Esempi di Applicazione:

```c
// Esempio 1: Dormire per 1 millisecondo
usleep(1000);

// Esempio 2: Dormire per 100 millisecondi
usleep(100000);

// Esempio 3: Dormire per 1 secondo
usleep(1000000);

// Esempio 4: Variabile (COME NEL PROGETTO FILOSOFI)
int time_to_eat = 200;  // 200 ms
usleep(time_to_eat * 1000);  // Converti a μs

// Esempio 5: In un ciclo
for (int i = 0; i < 5; i++) {
    printf("Ciclo %d\n", i);
    usleep(500000);  // 500 ms tra ogni ciclo
}

// Esempio 6: Nel thread filosofo
void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    
    while (1) {
        printf("Philosopher %d is thinking\n", philo->id);
        usleep(100000);  // Pensa per 100 ms
        
        printf("Philosopher %d is eating\n", philo->id);
        usleep(200000);  // Mangia per 200 ms
        
        printf("Philosopher %d is sleeping\n", philo->id);
        usleep(150000);  // Dorme per 150 ms
    }
    return (NULL);
}
```

### Utilità:
- **Simulare lavoro**: Nel progetto, rappresenta il tempo di mangiare/dormire
- **Evitare busy waiting**: Invece di loop vuoti, il thread dorme
- **Test/Debug**: Rallentare l'esecuzione per vedere cosa succede
- **Sincronizzazione temporale**: Coordina azioni basate su tempo

---

## **7. GETTIMEOFDAY**

### Prototipo:
```c
#include <sys/time.h>
int gettimeofday(struct timeval *tv, struct timezone *tz);
```

### Parametri:
- `tv` (struct timeval *): Puntatore a struttura da riempire
- `tz` (struct timezone *): Timezone (di solito NULL, deprecated)

### Ritorno:
- 0 se successo
- -1 se errore

### Struttura timeval:
```c
struct timeval {
    time_t tv_sec;       // Secondi dal 1 gennaio 1970
    suseconds_t tv_usec; // Microsecondi aggiuntivi (0-999999)
};
```

### Spiegazione:
Riempie la struttura `tv` con il tempo attuale del sistema in secondi + microsecondi. Utile per misurare il tempo trascorso e generare timestamp accurati.

### Esempi di Applicazione:

```c
// Esempio 1: Ottenere il tempo attuale
struct timeval tv;
gettimeofday(&tv, NULL);
printf("Secondi: %ld, Microsecondi: %ld\n", tv.tv_sec, tv.tv_usec);

// Esempio 2: Convertire a millisecondi
struct timeval tv;
gettimeofday(&tv, NULL);
long long ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
printf("Tempo in ms: %lld\n", ms);

// Esempio 3: Misurare tempo trascorso
struct timeval start, end;
gettimeofday(&start, NULL);

// ... fai qualcosa ...
usleep(100000);  // 100 ms

gettimeofday(&end, NULL);
long long elapsed = ((end.tv_sec * 1000) + (end.tv_usec / 1000)) 
                   - ((start.tv_sec * 1000) + (start.tv_usec / 1000));
printf("Tempo trascorso: %lld ms\n", elapsed);
// Output: Tempo trascorso: 100 ms (circa)

// Esempio 4: CRITICO PER FILOSOFI
typedef struct s_data {
    long long start_time;
} t_data;

void init_data(t_data *data) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

long long get_elapsed_time(t_data *data) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long current = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (current - data->start_time);
}

// Nel main:
t_data data;
init_data(&data);
usleep(500000);
printf("Tempo trascorso: %lld ms\n", get_elapsed_time(&data));
// Output: Tempo trascorso: 500 ms (circa)

// Esempio 5: Controllare se il filosofo è morto
void check_if_philosopher_died(t_philosopher *philo, t_data *data) {
    long long current_time = get_elapsed_time(data);
    long long time_since_last_meal = current_time - philo->last_meal_time;
    
    if (time_since_last_meal > data->time_to_die) {
        printf("%lld ms: Philosopher %d died\n", current_time, philo->id);
    }
}
```

### Utilità:
- **Timestamp accurati**: Sapere esattamente quando succede qualcosa
- **Misurare prestazioni**: Quanto tempo impiega un'operazione
- **Controllo timeout**: Verificare se è passato un certo tempo (morte filosofo)
- **Obbligatorio per Filosofi**: Output deve avere timestamp in ms

---

## **8. PTHREAD_CREATE**

### Prototipo:
```c
#include <pthread.h>
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
```

### Parametri:
- `thread` (pthread_t *): Puntatore a variabile che contiene l'ID del thread creato
- `attr` (const pthread_attr_t *): Attributi del thread (NULL per default)
- `start_routine` (void *(*)(void *)): Funzione da eseguire nel thread
- `arg` (void *): Argomento passato a start_routine

### Ritorno:
- 0 se successo
- non-zero (numero d'errore) se fallisce

### Spiegazione:
Crea un nuovo thread che esegue `start_routine` con argomento `arg`. Il nuovo thread parte parallelamente al thread che ha chiamato pthread_create. È fondamentale per il progetto Filosofi.

### Esempi di Applicazione:

```c
// Esempio 1: Thread semplice
void *my_thread(void *arg) {
    printf("Ciao dal thread!\n");
    return (NULL);
}

int main() {
    pthread_t tid;
    
    if (pthread_create(&tid, NULL, my_thread, NULL) != 0) {
        perror("pthread_create");
        return (1);
    }
    
    sleep(1);  // Aspetta che il thread finisca
    printf("Fine main\n");
    return (0);
}

// Esempio 2: Passare argomento al thread
void *thread_with_arg(void *arg) {
    int *num = (int *)arg;
    printf("Numero ricevuto: %d\n", *num);
    return (NULL);
}

int main() {
    pthread_t tid;
    int value = 42;
    
    if (pthread_create(&tid, NULL, thread_with_arg, &value) != 0) {
        perror("pthread_create");
        return (1);
    }
    
    pthread_join(tid, NULL);  // Aspetta
    printf("Thread finito\n");
    return (0);
}

// Esempio 3: Creare array di thread (IMPORTANTE PER FILOSOFI)
int num_philosophers = 5;
pthread_t *threads = malloc(sizeof(pthread_t) * num_philosophers);

for (int i = 0; i < num_philosophers; i++) {
    if (pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]) != 0) {
        perror("pthread_create");
        return (1);
    }
}

// Aspettare che finiscano
for (int i = 0; i < num_philosophers; i++) {
    pthread_join(threads[i], NULL);
}

free(threads);

// Esempio 4: Struttura per passare più dati
typedef struct s_args {
    int id;
    char *name;
    t_data *shared_data;
} t_args;

void *thread_with_struct(void *arg) {
    t_args *args = (t_args *)arg;
    printf("ID: %d, Nome: %s\n", args->id, args->name);
    return (NULL);
}

int main() {
    pthread_t tid;
    t_args args = {1, "Thread1", &data};
    
    if (pthread_create(&tid, NULL, thread_with_struct, &args) != 0) {
        perror("pthread_create");
        return (1);
    }
    
    pthread_join(tid, NULL);
    return (0);
}

// Esempio 5: NEL PROGETTO FILOSOFI
void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;
    
    while (!data->someone_died) {
        // Pensiare
        printf("Philosopher %d is thinking\n", philo->id);
        usleep(100000);
        
        // Mangiare
        // ... prendi forchette ...
        printf("Philosopher %d is eating\n", philo->id);
        usleep(data->time_to_eat * 1000);
        
        // Dormire
        printf("Philosopher %d is sleeping\n", philo->id);
        usleep(data->time_to_sleep * 1000);
    }
    return (NULL);
}

int main(int argc, char **argv) {
    int num = atoi(argv[1]);
    pthread_t *threads = malloc(sizeof(pthread_t) * num);
    t_philosopher *philosophers = malloc(sizeof(t_philosopher) * num);
    
    for (int i = 0; i < num; i++) {
        philosophers[i].id = i;
        philosophers[i].data = &data;
        
        if (pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]) != 0) {
            perror("pthread_create");
            return (1);
        }
    }
    
    for (int i = 0; i < num; i++)
        pthread_join(threads[i], NULL);
    
    free(threads);
    free(philosophers);
    return (0);
}
```

### Utilità:
- **Parallelismo**: Più operazioni contemporaneamente
- **Condivisione memoria**: Tutti i thread vedono le stesse variabili globali
- **Fondamentale per Filosofi**: Ogni filosofo è un thread separato

---

## **9. PTHREAD_DETACH**

### Prototipo:
```c
#include <pthread.h>
int pthread_detach(pthread_t thread);
```

### Parametri:
- `thread` (pthread_t): ID del thread da staccare

### Ritorno:
- 0 se successo
- non-zero se errore

### Spiegazione:
Marca il thread come "detached" - significa che si pulisce automaticamente quando termina. Non puoi più usare pthread_join() su un thread detached. È un'alternativa a join(), scelta in base alle necessità.

### Differenza: Join vs Detach
```
PTHREAD_JOIN:
- Il thread principale aspetta che i thread figli finiscono
- Controllato, sincronizzato
- Puoi recuperare il valore di ritorno

PTHREAD_DETACH:
- I thread si puliscono automaticamente
- Il programma continua indipendentemente
- Non puoi recuperare il valore di ritorno
```

### Esempi di Applicazione:

```c
// Esempio 1: Detach semplice
void *my_thread(void *arg) {
    printf("Thread in esecuzione\n");
    usleep(1000000);  // 1 secondo
    printf("Thread finito\n");
    return (NULL);
}

int main() {
    pthread_t tid;
    
    pthread_create(&tid, NULL, my_thread, NULL);
    pthread_detach(tid);  // Stacca il thread
    
    printf("Main continua\n");
    usleep(500000);  // 500 ms
    // A questo punto il thread sta ancora girando
    // Ma il programma non lo aspetta
    
    sleep(2);  // Aspetta che il thread finisca prima di uscire
    printf("Fine main\n");
    return (0);
}

// Esempio 2: Confronto join vs detach
// CON JOIN
void *thread_func(void *arg) {
    printf("Thread\n");
    return (NULL);
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(tid, NULL);  // Aspetta che termini
    printf("Thread finito, continuo\n");
    return (0);
}

// CON DETACH
int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_detach(tid);  // Non aspetta
    printf("Ho creato il thread (potrebbe non essere finito)\n");
    sleep(1);  // Devo io gestire l'attesa
    return (0);
}

// Esempio 3: Quando è utile il DETACH
// Per thread lunghi che non devono bloccare il main
void *server_thread(void *arg) {
    while (1) {
        printf("Server in esecuzione...\n");
        usleep(500000);
    }
    return (NULL);
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, server_thread, NULL);
    pthread_detach(tid);  // Il server gira in background
    
    printf("Server avviato\n");
    printf("Main può continuare a fare altre cose\n");
    
    sleep(10);  // Lascia il server girare
    return (0);
}

// Esempio 4: Nel progetto FILOSOFI (scelta: join o detach)
// OPZIONE 1: USANDO JOIN (più comune)
int main(int argc, char **argv) {
    int num = atoi(argv[1]);
    pthread_t *threads = malloc(sizeof(pthread_t) * num);
    t_philosopher *philosophers = malloc(sizeof(t_philosopher) * num);
    
    for (int i = 0; i < num; i++) {
        pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
    }
    
    // Aspetta che TUTTI i thread finiscano
    for (int i = 0; i < num; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Tutti i filosofi hanno finito\n");
    cleanup();
    return (0);
}

// OPZIONE 2: USANDO DETACH (meno comune)
int main(int argc, char **argv) {
    int num = atoi(argv[1]);
    pthread_t *threads = malloc(sizeof(pthread_t) * num);
    
    for (int i = 0; i < num; i++) {
        pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
        pthread_detach(threads[i]);  // Stacca ogni thread
    }
    
    // Il main continua, i thread si puliscono da soli
    // Ma devi gestire manualmente l'attesa
    while (!data->someone_died) {
        // Monitor i filosofi
        usleep(100000);
    }
    
    sleep(1);  // Aspetta che i thread finiscano
    cleanup();
    return (0);
}
```

### Utilità:
- **Pulizia automatica**: Il thread si pulisce senza richiedere join()
- **Leggerezza**: Riduce codice boilerplate
- **Asincrono**: Il main continua senza aspettare
- **Trade-off**: Meno controllo, meno sincronizzazione

---

## **10. PTHREAD_JOIN**

### Prototipo:
```c
#include <pthread.h>
int pthread_join(pthread_t thread, void **retval);
```

### Parametri:
- `thread` (pthread_t): ID del thread da aspettare
- `retval` (void **): Puntatore dove salvare il valore di ritorno del thread (NULL se non ti interessa)

### Ritorno:
- 0 se successo
- non-zero se errore

### Spiegazione:
Blocca il thread chiamante finché `thread` non termina. È il metodo principale per sincronizzare il main con i thread figli. Una volta fatto join, puoi leggere il valore di ritorno.

### Esempi di Applicazione:

```c
// Esempio 1: Join semplice
void *thread_func(void *arg) {
    printf("Thread in esecuzione\n");
    usleep(1000000);  // 1 secondo
    return (NULL);
}

int main() {
    pthread_t tid;
    printf("Inizio\n");
    
    pthread_create(&tid, NULL, thread_func, NULL);
    printf("Thread creato\n");
    
    pthread_join(tid, NULL);  // Aspetta qui finché non finisce
    printf("Thread finito\n");
    return (0);
}
// Output:
// Inizio
// Thread creato
// Thread in esecuzione
// (1 secondo di attesa)
// Thread finito

// Esempio 2: Recuperare valore di ritorno
void *thread_with_return(void *arg) {
    int *result = malloc(sizeof(int));
    *result = 42;
    return (result);  // Ritorna un puntatore
}

int main() {
    pthread_t tid;
    int *result = NULL;
    
    pthread_create(&tid, NULL, thread_with_return, NULL);
    pthread_join(tid, (void **)&result);  // Recupera il ritorno
    
    printf("Valore dal thread: %d\n", *result);
    free(result);
    return (0);
}

// Esempio 3: Creare più thread e aspettarli (IMPORTANTE PER FILOSOFI)
int num_threads = 5;
pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);

// Creare i thread
for (int i = 0; i < num_threads; i++) {
    if (pthread_create(&threads[i], NULL, thread_func, NULL) != 0) {
        perror("pthread_create");
        return (1);
    }
}

// Aspettare che TUTTI finiscano
for (int i = 0; i < num_threads; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
        perror("pthread_join");
        return (1);
    }
}

printf("Tutti i thread sono finiti\n");
free(threads);

// Esempio 4: Nel progetto FILOSOFI
void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    
    while (!philo->data->someone_died) {
        eat(philo);
        sleep(philo);
        think(philo);
    }
    
    return (NULL);  // Il thread termina
}

int main(int argc, char **argv) {
    int num_philosophers = atoi(argv[1]);
    
    pthread_t *threads = malloc(sizeof(pthread_t) * num_philosophers);
    t_philosopher *philosophers = malloc(sizeof(t_philosopher) * num_philosophers);
    
    // Inizializzare i filosofi
    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i].id = i;
        philosophers[i].data = &data;
    }
    
    // Creare i thread
    for (int i = 0; i < num_philosophers; i++) {
        if (pthread_create(&threads[i], NULL, philosopher_routine, 
                          &philosophers[i]) != 0) {
            perror("pthread_create");
            return (1);
        }
    }
    
    // Aspettare che finiscano TUTTI
    for (int i = 0; i < num_philosophers; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return (1);
        }
    }
    
    printf("Simulazione finita\n");
    cleanup(&data);
    free(threads);
    free(philosophers);
    return (0);
}

// Esempio 5: Gestire errori in join
for (int i = 0; i < num_philosophers; i++) {
    int ret = pthread_join(threads[i], NULL);
    if (ret != 0) {
        fprintf(stderr, "Errore join thread %d: %s\n", i, strerror(ret));
        // Continua comunque, o gestisci l'errore
    }
}
```

### Utilità:
- **Sincronizzazione**: Il main aspetta i thread
- **Controllo**: Sai quando un thread è veramente finito
- **Valore di ritorno**: Recupera dati dal thread
- **Essenziale per Filosofi**: Il programma aspetta che tutti i filosofi finiscano prima di uscire

---

## **11. PTHREAD_MUTEX_INIT**

### Prototipo:
```c
#include <pthread.h>
int pthread_mutex_init(pthread_mutex_t *mutex, 
                       const pthread_mutexattr_t *attr);
```

### Parametri:
- `mutex` (pthread_mutex_t *): Puntatore al mutex da inizializzare
- `attr` (const pthread_mutexattr_t *): Attributi (NULL per default)

### Ritorno:
- 0 se successo
- non-zero se errore

### Spiegazione:
Inizializza un mutex (mutual exclusion lock). Un mutex è un "lucchetto" che garantisce che solo un thread per volta acceda a una risorsa critica. Senza mutex, più thread che accedono alla stessa variabile creano race condition.

### Cos'è una Race Condition?
```c
// SENZA MUTEX
int counter = 0;

// Thread 1                    // Thread 2
counter++;                     counter++;
// Se entrambi leggono 0:
// T1: legge 0, scrive 1
// T2: legge 0, scrive 1
// Risultato atteso: 2
// Risultato reale: 1 (BUG!)

// CON MUTEX
pthread_mutex_lock(&mutex);
counter++;
pthread_mutex_unlock(&mutex);

// Ora è garantito che solo un thread per volta accede
```

### Esempi di Applicazione:

```c
// Esempio 1: Inizializzare un mutex
pthread_mutex_t my_mutex;

if (pthread_mutex_init(&my_mutex, NULL) != 0) {
    perror("pthread_mutex_init");
    return (1);
}

// Adesso puoi usarlo con lock/unlock

// Esempio 2: Struttura dati con mutex (IMPORTANTE PER FILOSOFI)
typedef struct s_data {
    int shared_variable;
    pthread_mutex_t var_lock;  // Proteggere shared_variable
} t_data;

int main() {
    t_data data;
    data.shared_variable = 0;
    
    if (pthread_mutex_init(&data.var_lock, NULL) != 0) {
        perror("pthread_mutex_init");
        return (1);
    }
    
    // ... usa il mutex ...
    
    pthread_mutex_destroy(&data.var_lock);
    return (0);
}

// Esempio 3: Array di mutex (CRITICO PER FILOSOFI - UNO PER FORCHETTA)
int num_philosophers = 5;
pthread_mutex_t *fork_locks = malloc(sizeof(pthread_mutex_t) * num_philosophers);

// Inizializzare TUTTI i mutex
for (int i = 0; i < num_philosophers; i++) {
    if (pthread_mutex_init(&fork_locks[i], NULL) != 0) {
        perror("pthread_mutex_init");
        return (1);
    }
}

// ... usa i mutex ...

// Distruggere TUTTI i mutex quando finito
for (int i = 0; i < num_philosophers; i++) {
    pthread_mutex_destroy(&fork_locks[i]);
}
free(fork_locks);

// Esempio 4: Struttura dati completa per FILOSOFI
typedef struct s_data {
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    
    pthread_mutex_t *fork_locks;      // Un mutex per ogni forchetta
    pthread_mutex_t print_lock;       // Proteggere printf
    pthread_mutex_t death_lock;       // Proteggere variabile "someone_died"
    
    int someone_died;
    long long start_time;
} t_data;

int init_data(t_data *data, int num) {
    data->fork_locks = malloc(sizeof(pthread_mutex_t) * num);
    if (!data->fork_locks)
        return (1);
    
    // Inizializzare i lock delle forchette
    for (int i = 0; i < num; i++) {
        if (pthread_mutex_init(&data->fork_locks[i], NULL) != 0) {
            perror("fork_lock init");
            return (1);
        }
    }
    
    // Inizializzare gli altri lock
    if (pthread_mutex_init(&data->print_lock, NULL) != 0) {
        perror("print_lock init");
        return (1);
    }
    
    if (pthread_mutex_init(&data->death_lock, NULL) != 0) {
        perror("death_lock init");
        return (1);
    }
    
    return (0);
}

// Esempio 5: Il ciclo di vita di un mutex
int main() {
    pthread_mutex_t mutex;
    
    // 1. Inizializzare
    pthread_mutex_init(&mutex, NULL);
    
    // 2. Usare (lock/unlock) - vedi prossime funzioni
    
    // 3. Distruggere quando finito
    pthread_mutex_destroy(&mutex);
    
    return (0);
}
```

### Utilità:
- **Protezione dati**: Previene race condition
- **Sincronizzazione**: Coordina accesso a risorse condivise
- **Fondamentale per Filosofi**: Un mutex per ogni forchetta
- **Thread-safe**: Garantisce coerenza dati

---

## **12. PTHREAD_MUTEX_LOCK**

### Prototipo:
```c
#include <pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mutex);
```

### Parametri:
- `mutex` (pthread_mutex_t *): Puntatore al mutex da acquisire

### Ritorno:
- 0 se successo
- non-zero se errore

### Spiegazione:
Acquisisce il mutex. Se il mutex è libero, lo prende immediatamente. Se è già acquisito da un altro thread, **ASPETTA** (blocca) finché non diventa libero. Solo un thread per volta può acquisire un mutex.

### Flow:
```
Thread A: lock()    -> acquista subito
Thread B: lock()    -> aspetta (mutex è occupato)
Thread A: unlock()  -> rilascia
Thread B: lock()    -> ora può acquisire
```

### Esempi di Applicazione:

```c
// Esempio 1: Proteggere una variabile
int shared_counter = 0;
pthread_mutex_t counter_lock;

void *increment_thread(void *arg) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&counter_lock);
        shared_counter++;  // Sezione critica
        pthread_mutex_unlock(&counter_lock);
    }
    return (NULL);
}

int main() {
    pthread_mutex_init(&counter_lock, NULL);
    
    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment_thread, NULL);
    pthread_create(&t2, NULL, increment_thread, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Counter: %d (deve essere 2000)\n", shared_counter);
    pthread_mutex_destroy(&counter_lock);
    return (0);
}

// Esempio 2: Sezione critica lunga
typedef struct s_data {
    int value;
    char name[50];
} t_data;

pthread_mutex_t data_lock;

void *modify_data(void *arg) {
    t_data *data = (t_data *)arg;
    
    pthread_mutex_lock(&data_lock);
    // Intera sezione è protetta
    data->value = 42;
    strcpy(data->name, "Modified");
    // Niente altro thread può entrare qui
    pthread_mutex_unlock(&data_lock);
    
    return (NULL);
}

// Esempio 3: Proteggere accesso a stdout (IMPORTANTE PER FILOSOFI)
pthread_mutex_t print_lock;

void safe_printf(const char *format, ...) {
    va_list args;
    pthread_mutex_lock(&print_lock);
    va_start(args, format);
    vprintf(format, args);  // printf thread-safe
    va_end(args);
    pthread_mutex_unlock(&print_lock);
}

// Nel thread:
safe_printf("%lld ms: Philosopher %d is eating\n", time, philo_id);

// Esempio 4: Proteggere array (CRITICO PER FILOSOFI)
// Prendersi una forchetta
void take_fork(int philo_id, int fork_id, t_data *data) {
    pthread_mutex_lock(&data->fork_locks[fork_id]);
    // Ora ho la forchetta
    printf("Philosopher %d took fork %d\n", philo_id, fork_id);
}

void put_fork(int fork_id, t_data *data) {
    pthread_mutex_unlock(&data->fork_locks[fork_id]);
    // Ho rilasciato la forchetta
}

// Esempio 5: Nel filosofo (PSEUDOCODICE FILOSOFI)
void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;
    
    while (!data->someone_died) {
        // PENSIARE (niente lock)
        
        // MANGIARE
        pthread_mutex_lock(&data->fork_locks[philo->left_fork]);
        pthread_mutex_lock(&data->fork_locks[philo->right_fork]);
        
        // Sezione critica: ho entrambe le forchette
        printf("Philosopher %d is eating\n", philo->id);
        usleep(data->time_to_eat * 1000);
        
        pthread_mutex_unlock(&data->fork_locks[philo->right_fork]);
        pthread_mutex_unlock(&data->fork_locks[philo->left_fork]);
        
        // DORMIRE
        printf("Philosopher %d is sleeping\n", philo->id);
        usleep(data->time_to_sleep * 1000);
    }
    
    return (NULL);
}

// Esempio 6: Deadlock (PERICOLO!)
// Se due thread si bloccano aspettando l'uno l'altro:
void *thread_bad(void *arg) {
    // Thread A:
    pthread_mutex_lock(&mutex1);
    usleep(100);
    pthread_mutex_lock(&mutex2);  // Aspetta mutex2
    // ...
    
    // Thread B (nel frattempo):
    // pthread_mutex_lock(&mutex2);
    // usleep(100);
    // pthread_mutex_lock(&mutex1);  // Aspetta mutex1 (DEADLOCK!)
}

// Soluzione: Acquisire SEMPRE nello stesso ordine
// BENE:
pthread_mutex_lock(&mutex1);
pthread_mutex_lock(&mutex2);
// ... sezione critica ...
pthread_mutex_unlock(&mutex2);
pthread_mutex_unlock(&mutex1);
```

### Utilità:
- **Sincronizzazione**: Permette un thread per volta
- **Protezione dati**: Evita race condition
- **Blocking**: Se il mutex è occupato, aspetta
- **Essenziale per Filosofi**: Proteggere le forchette

---

## **13. PTHREAD_MUTEX_UNLOCK**

### Prototipo:
```c
#include <pthread.h>
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

### Parametri:
- `mutex` (pthread_mutex_t *): Puntatore al mutex da rilasciare

### Ritorno:
- 0 se successo
- non-zero se errore

### Spiegazione:
Rilascia il mutex, permettendo ad altri thread di acquisirlo. Deve essere fatto SEMPRE dopo un lock. Simmetria: ogni lock() deve avere un unlock() corrispondente.

### Pattern fondamentale:
```
lock()
// sezione critica
unlock()
```

### Esempi di Applicazione:

```c
// Esempio 1: Lock-Unlock simmetrico
pthread_mutex_lock(&mutex);
// ... sezione critica ...
pthread_mutex_unlock(&mutex);

// Esempio 2: Proteggere una struttura
typedef struct s_value {
    int data;
} t_value;

pthread_mutex_t value_lock;
t_value value;

void *reader_thread(void *arg) {
    pthread_mutex_lock(&value_lock);
    int x = value.data;  // Leggi sicuro
    printf("Valore letto: %d\n", x);
    pthread_mutex_unlock(&value_lock);
    return (NULL);
}

void *writer_thread(void *arg) {
    pthread_mutex_lock(&value_lock);
    value.data = 42;  // Scrivi sicuro
    pthread_mutex_unlock(&value_lock);
    return (NULL);
}

// Esempio 3: Incrementare contatore (SICURO)
int counter = 0;
pthread_mutex_t counter_lock;

void *increment(void *arg) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&counter_lock);
        counter++;  // THREAD-SAFE
        pthread_mutex_unlock(&counter_lock);
    }
    return (NULL);
}

int main() {
    pthread_mutex_init(&counter_lock, NULL);
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Counter: %d (sarà esattamente 2000)\n", counter);
    pthread_mutex_destroy(&counter_lock);
    return (0);
}

// Esempio 4: Proteggere printf (IMPORTANTE PER FILOSOFI)
pthread_mutex_t print_lock;

void print_safely(const char *message, int id, long long time) {
    pthread_mutex_lock(&print_lock);
    printf("%lld ms: Philosopher %d %s\n", time, id, message);
    pthread_mutex_unlock(&print_lock);
}

// Esempio 5: Più mutex per proteggere diversi dati
typedef struct s_data {
    int counter;
    char message[100];
    pthread_mutex_t counter_lock;
    pthread_mutex_t message_lock;
} t_data;

void *worker(void *arg) {
    t_data *data = (t_data *)arg;
    
    // Modificare counter
    pthread_mutex_lock(&data->counter_lock);
    data->counter++;
    pthread_mutex_unlock(&data->counter_lock);
    
    // Modificare message (mutex diverso)
    pthread_mutex_lock(&data->message_lock);
    strcpy(data->message, "Updated");
    pthread_mutex_unlock(&data->message_lock);
    
    return (NULL);
}

// Esempio 6: FILOSOFI - Ciclo completo
void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;
    
    while (1) {
        // 1. PENSIARE (niente mutex)
        pthread_mutex_lock(&data->print_lock);
        printf("%lld ms: Philosopher %d is thinking\n", get_time(data), philo->id);
        pthread_mutex_unlock(&data->print_lock);
        
        usleep(100000);
        
        // 2. PRENDERE FORCHETTE (con mutex)
        pthread_mutex_lock(&data->fork_locks[philo->left_fork]);
        pthread_mutex_lock(&data->print_lock);
        printf("%lld ms: Philosopher %d has taken a fork\n", get_time(data), philo->id);
        pthread_mutex_unlock(&data->print_lock);
        
        pthread_mutex_lock(&data->fork_locks[philo->right_fork]);
        pthread_mutex_lock(&data->print_lock);
        printf("%lld ms: Philosopher %d has taken a fork\n", get_time(data), philo->id);
        pthread_mutex_unlock(&data->print_lock);
        
        // 3. MANGIARE
        pthread_mutex_lock(&data->print_lock);
        printf("%lld ms: Philosopher %d is eating\n", get_time(data), philo->id);
        pthread_mutex_unlock(&data->print_lock);
        
        usleep(data->time_to_eat * 1000);
        
        // 4. RILASCIARE FORCHETTE (unlock nell'ordine inverso)
        pthread_mutex_unlock(&data->fork_locks[philo->right_fork]);
        pthread_mutex_unlock(&data->fork_locks[philo->left_fork]);
        
        // 5. DORMIRE
        pthread_mutex_lock(&data->print_lock);
        printf("%lld ms: Philosopher %d is sleeping\n", get_time(data), philo->id);
        pthread_mutex_unlock(&data->print_lock);
        
        usleep(data->time_to_sleep * 1000);
        
        // Controllare se è morto
        if (is_philosopher_dead(philo, data))
            break;
    }
    
    return (NULL);
}

// Esempio 7: ATTENZIONE - Errore comune (DEADLOCK)
// SBAGLIATO: lock nello stesso ordine
pthread_mutex_lock(&m1);
// ... qualcosa ...
pthread_mutex_lock(&m2);
// ... sezione critica ...
pthread_mutex_unlock(&m2);
pthread_mutex_unlock(&m1);

// SE UN ALTRO THREAD FA:
pthread_mutex_lock(&m2);  // Mi blocco qui!
// ... mentre il primo thread aspetta m2 ...
// DEADLOCK!

// GIUSTO: Sempre nello stesso ordine
// Tutti i thread:
pthread_mutex_lock(&m1);
pthread_mutex_lock(&m2);
// ... sezione critica ...
pthread_mutex_unlock(&m2);
pthread_mutex_unlock(&m1);
```

### Utilità:
- **Rilasciare il lock**: Permette altri thread di accedere
- **Essenziale**: Senza unlock, altri thread si bloccano per sempre
- **Paired con lock**: Sempre lock() ... unlock()
- **Evitare deadlock**: Ordine consistente

---

## **14. PTHREAD_MUTEX_DESTROY**

### Prototipo:
```c
#include <pthread.h>
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

### Parametri:
- `mutex` (pthread_mutex_t *): Puntatore al mutex da distruggere

### Ritorno:
- 0 se successo
- non-zero se errore (es. il mutex è ancora locked)

### Spiegazione:
Distrugge un mutex e libera le risorse associate. Deve essere fatto DOPO aver finito di usare il mutex. Se il mutex è ancora locked, pthread_mutex_destroy() può fallire.

### Ciclo di vita di un mutex:
```
1. pthread_mutex_init()     <- Crea
2. pthread_mutex_lock()     <- Usa
3. pthread_mutex_unlock()
4. ... loop ...
5. pthread_mutex_destroy()  <- Distrugge
```

### Esempi di Applicazione:

```c
// Esempio 1: Destroy semplice
pthread_mutex_t mutex;

int main() {
    // Inizializzare
    pthread_mutex_init(&mutex, NULL);
    
    // Usare...
    pthread_mutex_lock(&mutex);
    // ... sezione critica ...
    pthread_mutex_unlock(&mutex);
    
    // Distruggere quando finito
    if (pthread_mutex_destroy(&mutex) != 0) {
        perror("pthread_mutex_destroy");
        return (1);
    }
    
    return (0);
}

// Esempio 2: Destroy array di mutex (IMPORTANTE PER FILOSOFI)
int num_philosophers = 5;
pthread_mutex_t *fork_locks = malloc(sizeof(pthread_mutex_t) * num_philosophers);

// Inizializzare
for (int i = 0; i < num_philosophers; i++) {
    pthread_mutex_init(&fork_locks[i], NULL);
}

// ... usa i mutex ...

// Distruggere TUTTI i mutex
for (int i = 0; i < num_philosophers; i++) {
    if (pthread_mutex_destroy(&fork_locks[i]) != 0) {
        perror("pthread_mutex_destroy");
        return (1);
    }
}

free(fork_locks);

// Esempio 3: Funzione di cleanup (UTILE PER FILOSOFI)
void cleanup_data(t_data *data, int num_philosophers) {
    // Distruggere i lock delle forchette
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&data->fork_locks[i]);
    }
    
    // Distruggere gli altri lock
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->death_lock);
    
    // Liberare memoria
    free(data->fork_locks);
}

// Nel main:
int main(int argc, char **argv) {
    int num = atoi(argv[1]);
    t_data data;
    
    init_data(&data, num);
    
    // ... esegui la simulazione ...
    
    cleanup_data(&data, num);  // Cleanup
    return (0);
}

// Esempio 4: Ordine corretto di cleanup
int main() {
    t_data data;
    pthread_t *threads;
    
    data.num_philosophers = 5;
    init_data(&data);
    
    // Creare thread
    threads = malloc(sizeof(pthread_t) * data.num_philosophers);
    for (int i = 0; i < data.num_philosophers; i++) {
        pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
    }
    
    // Aspettare i thread
    for (int i = 0; i < data.num_philosophers; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // ORDINE DI CLEANUP:
    // 1. Prima aspettare i thread (fatto)
    // 2. Poi distruggere i mutex
    for (int i = 0; i < data.num_philosophers; i++) {
        pthread_mutex_destroy(&data->fork_locks[i]);
    }
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->death_lock);
    
    // 3. Poi liberare la memoria
    free(threads);
    free(data.fork_locks);
    
    return (0);
}

// Esempio 5: Errore comune (NON FARE!)
int main() {
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    
    pthread_mutex_lock(&mutex);
    // ERRORE: Destroy mentre è locked!
    pthread_mutex_destroy(&mutex);  // Fallirà
    pthread_mutex_unlock(&mutex);   // Troppo tardi
    
    return (0);
}

// GIUSTO:
int main() {
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    
    pthread_mutex_lock(&mutex);
    // sezione critica
    pthread_mutex_unlock(&mutex);  // Unlock prima di destroy
    
    pthread_mutex_destroy(&mutex);  // Adesso funziona
    
    return (0);
}

// Esempio 6: Completo - FILOSOFI
void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;
    
    while (1) {
        // ... mangia, dorme, pensa ...
        
        // Controllare morte
        pthread_mutex_lock(&data->death_lock);
        if (data->someone_died) {
            pthread_mutex_unlock(&data->death_lock);
            break;  // Esce dal while
        }
        pthread_mutex_unlock(&data->death_lock);
    }
    
    return (NULL);  // Thread termina
}

int main(int argc, char **argv) {
    int num = atoi(argv[1]);
    t_data data;
    pthread_t *threads;
    
    // Setup
    data.number_of_philosophers = num;
    data.time_to_die = atoi(argv[2]);
    data.time_to_eat = atoi(argv[3]);
    data.time_to_sleep = atoi(argv[4]);
    
    // Allocare memoria
    threads = malloc(sizeof(pthread_t) * num);
    data.fork_locks = malloc(sizeof(pthread_mutex_t) * num);
    
    // Inizializzare mutex
    for (int i = 0; i < num; i++) {
        pthread_mutex_init(&data.fork_locks[i], NULL);
    }
    pthread_mutex_init(&data.print_lock, NULL);
    pthread_mutex_init(&data.death_lock, NULL);
    
    // Creare e aspettare thread
    for (int i = 0; i < num; i++) {
        pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
    }
    
    for (int i = 0; i < num; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // CLEANUP - Ordine corretto:
    // 1. Distruggere mutex (thread già terminati)
    for (int i = 0; i < num; i++) {
        pthread_mutex_destroy(&data.fork_locks[i]);
    }
    pthread_mutex_destroy(&data.print_lock);
    pthread_mutex_destroy(&data.death_lock);
    
    // 2. Liberare memoria
    free(threads);
    free(data.fork_locks);
    
    return (0);
}
```

### Utilità:
- **Pulizia risorse**: Libera risorse di sistema
- **Essenziale**: Non fare destroy() causa memory leak (a livello di sistema)
- **Ordine**: Destroy() DOPO che i thread hanno finito di usare il mutex
- **Prevenire deadlock**: Se un mutex è locked, destroy() fallisce (utile per debug)

---

## 📋 RIASSUNTO TABELLARE

| Funzione | Categoria | Scopo Principale | Cruciale per Filosofi? |
|----------|-----------|------------------|------------------------|
| `memset` | Memoria | Riempire memoria con valore | ✓ Setup |
| `malloc` | Memoria | Allocare memoria dinamica | ✓ Setup |
| `free` | Memoria | Liberare memoria | ✓ Cleanup |
| `printf` | I/O | Stampare formattato | ✓ Output |
| `write` | I/O | Scrivere su file descriptor | - (alternativa) |
| `usleep` | Timing | Pausa in microsecondi | ✓ Simulazione |
| `gettimeofday` | Timing | Ottenere tempo attuale | ✓ Timestamp |
| `pthread_create` | Thread | Creare thread | ✓✓✓ Core |
| `pthread_detach` | Thread | Staccare thread | - (alternativa join) |
| `pthread_join` | Thread | Aspettare thread | ✓✓ Sincronizzazione |
| `pthread_mutex_init` | Mutex | Inizializzare mutex | ✓✓✓ Core |
| `pthread_mutex_lock` | Mutex | Acquisire mutex | ✓✓✓ Core |
| `pthread_mutex_unlock` | Mutex | Rilasciare mutex | ✓✓✓ Core |
| `pthread_mutex_destroy` | Mutex | Distruggere mutex | ✓ Cleanup |

---

## 🎯 COME USARE QUESTO DOCUMENTO

1. **Leggi la teoria**: Comprendi cosa sono i thread e i mutex
2. **Per ogni funzione**:
   - Leggi il prototipo
   - Capisce i parametri
   - Studia gli esempi
   - Capisci l'utilità
3. **Applica al progetto**: Ricorda che nei Filosofi userai:
   - `pthread_create()`: Creare i 5 filosofi
   - `pthread_join()`: Aspettare che finiscano
   - `pthread_mutex_init/lock/unlock/destroy()`: Proteggere le forchette
   - `gettimeofday()`: Generare timestamp
   - `usleep()`: Simulare mangiare/dormire
   - `printf()`: Output (con mutex per sync)

Buon lavoro! 🚀

