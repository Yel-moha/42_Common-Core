# Guida per la Difesa - Philosophers Project

## DOMANDE SU PHILO CODE

### ✅ 1. "Ensure the code of philo complies with the following requirements"

**Risposta:** Sì, il mio codice soddisfa tutti i requisiti del progetto.

---

### ✅ 2. "Check there is one thread per philosopher"

**Come verificare:**
- **File:** [threads.c](threads.c#L25-L34)
- **Funzione:** `create_threads()`

```c
void	create_threads(t_philos *philos, t_data *data)
{
	long	i;
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread_id, NULL,
				philo_routine, &philos[i]) != 0)
			perror("Failed create thread");
		i++;
	}
}
```

**Spiegazione:** Creo esattamente `num_philos` thread usando `pthread_create()`. Ogni filosofo ha un proprio `thread_id` salvato nella struttura `t_philos`.

---

### ✅ 3. "Check there is only one fork per philosopher"

**Come verificare:**
- **File:** [parse_and_simulate.c](parse_and_simulate.c#L60-L75)
- **Funzione:** `forks_for_philos()`

```c
void	forks_for_philos(t_fork *forks, t_data *data, t_philos *philos)
{
	long	i;
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].is_full = false;
		philos[i].last_time_meal = data->start_time;
		philos[i].left_fork = &forks[i];                    // Forchetta sinistra
		philos[i].right_fork = &forks[(i + 1) % data->num_philos];  // Forchetta destra
		philos[i].data = data;
		i++;
	}
}
```

**Spiegazione:** Ogni filosofo ha esattamente 2 forchette (sinistra e destra), conformemente al problema dei filosofi a cena. Creo `num_philos` forchette totali. Filosofo `i` usa:
- Forchetta sinistra: `forks[i]`
- Forchetta destra: `forks[(i+1) % num_philos]`

Questo crea una configurazione circolare naturale dove le forchette sono condivise tra filosofi adiacenti.

---

### ✅ 4. "Check if there is a mutex per fork and that it's used to check the fork value and/or change it"

**Come verificare:**
- **File:** [philo.h](philo.h#L26-L30)
- **Definizione struttura fork:**

```c
typedef struct s_fork
{
	t_mutex	fork;        // MUTEX per proteggere l'accesso
	int		id_fork;     // ID identificativo
}	t_fork;
```

- **File:** [routine.c](routine.c#L71-L93)
- **Funzione:** `try_take_forks()` - come viene usato il mutex:

```c
int	try_take_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork);      // 🔒 LOCK
		print(philo, "has taken a fork");
		if (check_the_end(philo->data) || philo->data->num_philos == 1)
		{
			pthread_mutex_unlock(&philo->left_fork->fork); // 🔓 UNLOCK
			return (0);
		}
		pthread_mutex_lock(&philo->right_fork->fork);     // 🔒 LOCK
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);     // 🔒 LOCK
		print(philo, "has taken a fork");
		if (check_the_end(philo->data) || philo->data->num_philos == 1)
		{
			pthread_mutex_unlock(&philo->right_fork->fork); // 🔓 UNLOCK
			return (0);
		}
		pthread_mutex_lock(&philo->left_fork->fork);      // 🔒 LOCK
		print(philo, "has taken a fork");
	}
	return (1);
}
```

- **File:** [routine_helpers.c](routine_helpers.c#L16-L19)
- **Funzione:** `release_forks()` - rilascio delle forchette:

```c
void	release_forks(t_philos *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork);        // 🔓 UNLOCK
	pthread_mutex_unlock(&philo->right_fork->fork);       // 🔓 UNLOCK
}
```

**Spiegazione:** Ogni forchetta è protetta da un mutex. Quando un filosofo vuole prendere una forchetta, fa `lock()`. Quando la rilascia, fa `unlock()`. Questo previene due thread di usare la stessa forchetta contemporaneamente.

---

### ✅ 5. "Check the outputs are never mixed up"

**Come verificare:**
- **File:** [print.c](print.c)
- **Funzione:** `print()` - output sincronizzato:

```c
void	print(t_philos *philo, const char *state)
{
	long	timestamp;

	if (check_the_end(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);  // 🔒 Sincronizzazione
	timestamp = get_timestamp(philo->data->start_time);
	printf("[%ld] Philosopher %d %s\n", timestamp, philo->id, state);
	pthread_mutex_unlock(&philo->data->print_mutex); // 🔓 Rilascio
}
```

**Spiegazione:** Uso un mutex dedicato (`print_mutex`) per sincronizzare tutte le stampe. Quando un thread stampa, blocca il mutex, stampa atomicamente, e poi lo rilascia. Questo garantisce che le righe non si mescolano mai, anche con molti thread che stampano contemporaneamente.

---

### ✅ 6. "Check how the death of a philosopher is verified and if there is a mutex to prevent a philosopher from dying and starting eating at the same time"

**Come verificare:**

**Parte 1 - Verifica della morte:**
- **File:** [routine_helpers.c](routine_helpers.c#L43-L57)
- **Funzione:** `is_dead()`

```c
int	is_dead(t_philos *philo, t_data *data)
{
	long	last_meal;
	long	time_since_last_meal;

	last_meal = get_last_meal_time(philo);          // Leggi l'ultimo pasto (thread-safe)
	time_since_last_meal = get_time_in_millis() - last_meal;
	if (time_since_last_meal > data->time_to_die)  // Se tempo > soglia
	{
		print_the_end(philo, data);                // Stampa "died"
		pthread_mutex_lock(&data->end_mutex);      // 🔒 Sincronizza flag globale
		data->end_exec = true;                     // Ferma tutti i thread
		pthread_mutex_unlock(&data->end_mutex);    // 🔓
		return (1);
	}
	return (0);
}
```

**Parte 2 - Thread monitor che controlla la morte:**
- **File:** [threads.c](threads.c#L94-L100)
- **Funzione:** `philos_master()` - il monitor thread

```c
void	*philos_master(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!check_the_end(data))
	{
		check_full_stop(data);  // Controlla se c'è morte o tutti pieni
		usleep(100);
	}
```

**Parte 3 - Protezione: Mutex per i pasti (`meal_mutexes`):**
- **File:** [philo.h](philo.h#L45)
- **Struttura dati:**

```c
typedef struct s_data
{
	...
	pthread_mutex_t	*meal_mutexes;  // Un mutex per OGNI filosofo
	...
}	t_data;
```

- **File:** [routine_helpers.c](routine_helpers.c#L21-L30)
- **Funzione:** `eat_action()` - aggiornamento pasti sincronizzato

```c
void	eat_action(t_philos *philo)
{
	print(philo, "is eating");
	update_last_meal(philo);                                    // Aggiorna l'ora dell'ultimo pasto
	pthread_mutex_lock(&philo->data->meal_mutexes[philo->id - 1]);  // 🔒
	philo->meals_eaten++;                                      // Incrementa pasti
	if (philo->data->max_meals > 0
		&& philo->meals_eaten >= philo->data->max_meals)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->data->meal_mutexes[philo->id - 1]); // 🔓
	ft_usleep(philo->data, philo->data->time_to_eat);
}
```

**Spiegazione del meccanismo di sincronizzazione:**

1. **Il monitor thread** controlla continuamente se un filosofo è morto (tempo dal ultimo pasto > time_to_die)
2. **Quando una morte è rilevata**, il flag `end_exec` viene impostato con protezione del mutex `end_mutex`
3. **Protezione dai meal_mutexes**: Quando un filosofo sta mangiando, il suo `meal_mutex` è locked. Il monitor quindi:
   - Può leggere `last_time_meal` (protetto da `time_mutex`)
   - Non può interruppere il filosofo durante il pasto perché è occupato con le forchette

4. **Risultato**: Un filosofo NON può contemporaneamente morire e mangiare perché:
   - Il monitor che verifica la morte legge `last_time_meal` in modo thread-safe
   - L'ultimo pasto viene aggiornato in modo atomico
   - Se il tempo > `time_to_die`, il flag `end_exec` ferma immediatamente tutti i thread

---

## DOMANDE SU PHILO TESTING

### Test Scenario Analysis

#### Test 1: `./philo 1 800 200 200` - Un filosofo deve morire
**Spiegazione:** Con solo 1 filosofo, non ci sono 2 forchette disponibili, quindi il filosofo non può mangiare e muore di fame dopo 800ms.
- **Risultato atteso:** Filosofo muore dopo ~800ms
- **Come è gestito nel codice:** Il check `philo->data->num_philos == 1` in `try_take_forks()` previene il deadlock

#### Test 2: `./philo 5 800 200 200` - Nessun filosofo muore
**Spiegazione:** 200ms a mangiare + 200ms a dormire = 400ms ciclo. In 800ms, ogni filosofo riesce a mangiare almeno una volta.
- **Risultato atteso:** Nessuna morte
- **Coordinamento:** La routine alterna filosofi pari e dispari per evitare deadlock

#### Test 3: `./philo 5 800 200 200 7` - Nessun filosofo muore, stop dopo 7 pasti
**Spiegazione:** Stesso di Test 2, ma il programma termina dopo che ogni filosofo ha mangiato 7 volte.
- **Risultato atteso:** Nessuna morte, stop coordinato
- **Come è gestito:** `check_full_stop()` verifica se `all_philos_full()` ritorna true

#### Test 4: `./philo 4 410 200 200` - Nessun filosofo muore
**Spiegazione:** 4 filosofi possono sempre trovare 2 forchette disponibili nel ciclo di 410ms.
- **Risultato atteso:** Nessuna morte

#### Test 5: `./philo 4 310 200 100` - Un filosofo muore
**Spiegazione:** Solo 100ms di sonno, ma 200ms per mangiare. Non c'è tempo per tutti di mangiare prima che il primo muoia.
- **Risultato atteso:** Un filosofo muore

---

## RACE CONDITIONS RISOLTE

Vedi [RACE_CONDITIONS_SOLVED.md](RACE_CONDITIONS_SOLVED.md) per:

1. **Deadlock con 1 filosofo** - Risolto con check speciale in `try_take_forks()`
2. **Data race su `we_all_exist`** - Risolto usando `start_mutex` per sincronizzare il flag
3. **Data race su `last_time_meal`** - Risolto usando `time_mutex` per letture atomiche
4. **Data race su `end_exec`** - Risolto usando `end_mutex`

---

## PUNTI CHIAVE DA RICORDARE

✅ **Un thread per filosofo** - Creato in `create_threads()`
✅ **Una forchetta per filosofo** (2 per mangiare) - Configurazione in `forks_for_philos()`
✅ **Un mutex per forchetta** - Struttura `s_fork` contiene il mutex
✅ **Output sincronizzato** - Tutti gli `printf()` protetti da `print_mutex`
✅ **Morte verificata safely** - Thread monitor con `is_dead()` + mutex di protezione
✅ **Nessuna race condition** - Tutti i dati condivisi protetti da mutex
✅ **No deadlock** - Ordinamento fisso (pari prendo sinistra prima, dispari prendo destra prima)

---

## STRUTTURA DEI MUTEX

```
┌─────────────────────────────────────┐
│  MUTEX USAGE IN DATA STRUCTURE      │
├─────────────────────────────────────┤
│ print_mutex      → Sincronizza I/O  │
│ time_mutex       → Legge safe       │
│ end_mutex        → Flag end_exec    │
│ start_mutex      → Sincronizza boot │
│ meal_mutexes[N]  → Pasti per phil   │
│ fork[N].fork     → Una per forchetta│
└─────────────────────────────────────┘
```

---

## COME TESTARE

```bash
# Test 1: Un filosofo - muore
./philo 1 800 200 200

# Test 2: Nessuna morte
./philo 5 800 200 200

# Test 3: Stop dopo 7 pasti
./philo 5 800 200 200 7

# Test 4: Nessuna morte
./philo 4 410 200 200

# Test 5: Una morte
./philo 4 310 200 100

# Con Valgrind (assicurati no data races)
valgrind --tool=helgrind --suppressions=suppressions.txt ./philo 5 800 200 200
```

---

**Preparato per la difesa! Buona fortuna! 🎓**
