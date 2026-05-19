# Picoshell: guida pratica alle funzioni utili

Questa nota serve a capire bene le funzioni che userai per l’esercizio `picoshell` e, soprattutto, **perché** servono tutte insieme per costruire una pipeline come fa una shell.

L’idea dell’esercizio è questa:

- hai una lista di comandi, per esempio:
  - `ls`
  - `grep picoshell`
  - `wc -l`
- devi eseguire ogni comando in un processo diverso
- l’output del primo comando deve diventare l’input del secondo
- l’output del secondo deve diventare l’input del terzo, e così via

In pratica stai ricreando il comportamento di:

```bash
ls | grep picoshell | wc -l
```

## Il modello mentale corretto

Una pipeline non è un unico processo che fa tutto. È una **catena di processi** collegati da pipe.

Ogni processo ha i suoi file descriptor standard:

- `stdin` = input standard, di solito file descriptor `0`
- `stdout` = output standard, di solito file descriptor `1`
- `stderr` = errori standard, file descriptor `2`

Per fare una pipeline devi cambiare dove leggono e scrivono i processi:

- il primo comando scrive nella pipe
- il comando successivo legge dalla pipe precedente e scrive nella pipe successiva
- l’ultimo comando legge dalla pipe precedente e scrive sullo schermo

Per ottenere questo comportamento servono soprattutto queste funzioni:

- `pipe`
- `fork`
- `dup2`
- `execvp`
- `close`
- `wait`
- `exit`

---

## `pipe`

### A cosa serve

`pipe` crea un canale di comunicazione tra processi.

La chiamata è:

```c
int pipe(int fd[2]);
```

Quando va a buon fine, `fd` viene riempito con due file descriptor:

- `fd[0]` = estremità di lettura
- `fd[1]` = estremità di scrittura

Quindi:

- scrivi in `fd[1]`
- leggi da `fd[0]`

### Esempio semplice

```c
int fd[2];

pipe(fd);
```

Ora puoi immaginare `fd` come un tubo:

- un processo mette dati dentro
- un altro processo li prende fuori

### Perché serve in `picoshell`

Ogni collegamento tra due comandi richiede una pipe.

Per esempio, con:

```bash
echo hello | cat
```

serve una pipe per far arrivare `hello` da `echo` a `cat`.

### Errore comune

Se non chiudi le estremità inutili della pipe, il processo che legge può rimanere bloccato in attesa di EOF, perché almeno un processo continua a tenere aperto il lato di scrittura.

---

## `fork`

### A cosa serve

`fork` crea un nuovo processo copiando quello corrente.

La chiamata è:

```c
pid_t fork(void);
```

Dopo `fork` esistono due processi:

- il padre
- il figlio

Il valore di ritorno ti dice in quale processo sei:

- `0` nel figlio
- `> 0` nel padre, e il valore è il PID del figlio
- `-1` in caso di errore

### Esempio mentale

```c
pid_t pid = fork();

if (pid == 0)
{
    // figlio
}
else
{
    // padre
}
```

### Perché serve in `picoshell`

Ogni comando della pipeline deve correre in un processo separato.

Se hai 3 comandi, devi creare 3 processi figlio. Il processo principale non deve eseguire direttamente i comandi, ma solo organizzare la pipeline.

### Cosa succede ai file descriptor dopo `fork`

Il figlio eredita i file descriptor aperti dal padre.

Questo è fondamentale: se il padre ha già creato una pipe, il figlio vede quella stessa pipe e può usarla con `dup2`.

### Errore comune

Non controllare il ritorno di `fork` è pericoloso: se `fork` fallisce, devi gestire l’errore e chiudere tutto quello che hai aperto.

---

## `dup2`

### A cosa serve

`dup2` duplica un file descriptor su un altro file descriptor specifico.

La chiamata è:

```c
int dup2(int oldfd, int newfd);
```

Significa:

- `newfd` viene chiuso se era già aperto
- poi `newfd` diventa una copia di `oldfd`

### Esempio pratico

Se vuoi che un processo legga dalla pipe invece che da tastiera, fai:

```c
dup2(fd[0], 0);
```

Ora il file descriptor `0` (`stdin`) punta alla lettura della pipe.

Se vuoi che un processo scriva nella pipe invece che sullo schermo, fai:

```c
dup2(fd[1], 1);
```

Ora `stdout` punta alla scrittura della pipe.

### Perché è importantissima

`execvp` esegue un programma esterno che, normalmente, legge da `stdin` e scrive su `stdout`.

Con `dup2` modifichi questi canali **prima** di chiamare `execvp`, così il programma non si accorge di nulla e funziona come in una shell.

### Esempio concettuale

Per eseguire:

```bash
cat < input.txt | grep hello
```

non devi insegnare a `cat` o `grep` cosa sia una pipe. Devi solo:

- collegare `stdout` del primo comando alla pipe
- collegare `stdin` del secondo comando alla stessa pipe

### Errore comune

Spostare i descrittori senza `dup2` non basta. Devi proprio rimappare `stdin` o `stdout` sui descrittori della pipe.

---

## `execvp`

### A cosa serve

`execvp` sostituisce il processo corrente con un nuovo programma.

La chiamata è:

```c
int execvp(const char *file, char *const argv[]);
```

### Concetto fondamentale

`execvp` **non crea un nuovo processo**.

Sostituisce il programma del processo attuale.

Quindi di solito fai:

1. `fork`
2. nel figlio sistemi `stdin` e `stdout` con `dup2`
3. nel figlio chiami `execvp`

Se `execvp` riesce, non torna più indietro.

### Esempio

Se hai:

```c
char *cmd[] = {"/bin/ls", "-l", NULL};
execvp(cmd[0], cmd);
```

il processo corrente viene trasformato nel programma `ls -l`.

### Perché si usa `cmd[0]`

Nel tuo esercizio ogni riga di `cmds` è già un array `argv` pronto da passare a `execvp`.

Quindi:

- `cmds[i][0]` è il nome del comando o il percorso
- `cmds[i][1]`, `cmds[i][2]`, ... sono gli argomenti

### Esempio con il tuo esercizio

Se `cmds[i]` vale:

```c
{ "grep", "picoshell", NULL }
```

allora puoi fare direttamente:

```c
execvp(cmds[i][0], cmds[i]);
```

### Errore comune

Se `execvp` fallisce, il figlio non deve continuare come se niente fosse. Deve terminare con `exit(1)` o comunque uscire correttamente.

---

## `close`

### A cosa serve

`close` chiude un file descriptor.

La chiamata è:

```c
int close(int fd);
```

### Perché è cruciale nelle pipeline

Ogni processo eredita file descriptor che non gli servono.

Se lasci aperte troppe estremità della pipe, il comportamento della pipeline può rompersi.

### Regola pratica

Dopo `fork`:

- il figlio deve chiudere i descrittori che non usa
- il padre deve chiudere i descrittori che non usa

### Esempio

Se un figlio usa solo la scrittura della pipe, deve chiudere la lettura.

Se un figlio usa solo la lettura della pipe, deve chiudere la scrittura.

### Perché è così importante

Immagina una pipeline con due processi. Se anche solo un processo tiene aperta la scrittura della pipe, il lettore potrebbe non ricevere mai la fine del flusso.

Questo è uno dei motivi più comuni per cui una pipeline “sembra bloccata”.

---

## `wait`

### A cosa serve

`wait` attende la terminazione di un processo figlio.

La chiamata è:

```c
pid_t wait(int *status);
```

### Perché serve qui

L’esercizio dice che, se tutto va bene, devi:

- eseguire tutti i figli
- aspettare che finiscano
- restituire `0`

Quindi il processo padre non deve terminare subito. Deve raccogliere i figli.

### Esempio concettuale

Se crei 3 figli, il padre deve fare `wait` tre volte.

### Cosa ti dà `wait`

Il parametro `status` può contenere informazioni sul risultato dell’esecuzione del figlio.

In questo esercizio di solito ti interessa soprattutto aspettare che tutti finiscano, non analizzare in dettaglio il codice di uscita.

### Errore comune

Se non fai `wait`, lasci processi zombie.

---

## `exit`

### A cosa serve

`exit` termina il processo corrente.

La chiamata è:

```c
void exit(int status);
```

### Perché serve nel figlio

Nel figlio, se `execvp` fallisce, devi uscire subito con un codice di errore.

Inoltre, in alcuni casi, se hai appena finito di preparare la pipeline e vuoi interrompere il flusso per un errore, il figlio deve terminare.

### Esempio tipico

```c
execvp(cmd[0], cmd);
exit(1);
```

La riga dopo `execvp` viene eseguita solo se `execvp` fallisce.

### Attenzione

Nell’esercizio è permessa `exit`, non `return` dal processo figlio se il figlio si trova dentro una funzione che deve terminare il programma. Il senso è: se il figlio non può più continuare, termina davvero.

---

## Come si combinano tutte queste funzioni

Il flusso classico per una pipeline è questo:

1. per ogni comando, crea una pipe se non sei sull’ultimo comando
2. fai `fork`
3. nel figlio:
   - se c’è una pipe precedente, collega `stdin` con `dup2`
   - se c’è una pipe successiva, collega `stdout` con `dup2`
   - chiudi i file descriptor inutili
   - chiama `execvp`
   - se `execvp` fallisce, chiama `exit(1)`
4. nel padre:
   - chiudi le estremità della pipe che non servono più
   - salva il PID del figlio
5. alla fine aspetta tutti i figli con `wait`

---

## Esempio completo 1: due comandi

Pipeline:

```bash
echo hello | cat
```

### Passi mentali

1. crei una pipe
2. fai `fork`
3. nel figlio di `echo`:
   - `stdout` viene collegato alla scrittura della pipe
   - `echo` scrive `hello` nella pipe
4. nel figlio di `cat`:
   - `stdin` viene collegato alla lettura della pipe
   - `cat` legge `hello` e lo riscrive su schermo
5. il padre chiude tutto e aspetta

### Risultato

```bash
hello
```

---

## Esempio completo 2: tre comandi

Pipeline:

```bash
echo squalala | cat | sed 's/a/b/g'
```

### Flusso dei dati

- `echo` produce `squalala`
- `cat` riceve `squalala` e lo rimanda uguale
- `sed` trasforma le `a` in `b`

### Risultato

```bash
squblblb
```

---

## Struttura minima di una pipeline corretta

Questa è la logica che devi tenere in testa, senza fissarti subito sul codice finale:

```c
for each command
    if not last command
        create a pipe

    fork

    if child
        if there is previous pipe
            dup2(previous_read_end, 0)
        if there is next pipe
            dup2(current_write_end, 1)
        close all unused fds
        execvp(cmd[0], cmd)
        exit(1)

    if parent
        close fds no longer needed

wait for all children
```

---

## Errori tipici da evitare

### 1. Dimenticare di chiudere le pipe

Sintomo: il programma si blocca.

### 2. Fare `execvp` nel padre

Sintomo: il processo principale viene sostituito e non può più gestire gli altri comandi.

### 3. Non fare `fork`

Sintomo: non hai processi separati, quindi non hai una vera pipeline.

### 4. Non fare `wait`

Sintomo: processi zombie.

### 5. Non gestire gli errori delle syscall

Sintomo: comportamenti strani o risorse lasciate aperte.

---

## Mini riassunto finale

- `pipe` crea il collegamento tra due processi
- `fork` crea un nuovo processo
- `dup2` collega `stdin` o `stdout` a una pipe
- `execvp` esegue il comando nel figlio
- `close` chiude i descrittori inutili
- `wait` aspetta che i figli finiscano
- `exit` termina il figlio in caso di errore

Se capisci bene questi sette concetti, l’esercizio `picoshell` diventa molto più leggibile.
