# MINISHELL - DOMANDE "TRICKY" E RISPOSTE

## Domande Difficili Che il Correttore Potrebbe Fare

---

## 1️⃣ "E se durante una pipe il primo comando produce molto output?"

**Domanda tricky:** Come evitate di riempire la memoria?

**Risposta completa:**
Le pipe in Unix funzionano con un buffer limitato (solitamente 64KB). Se il primo comando produce troppo output:
1. Scrive nel buffer della pipe
2. Quando il buffer è pieno, `write()` si blocca
3. Il secondo comando continua a leggere dal buffer
4. Una volta che legge, il buffer si libera
5. Il primo comando può scrivere ancora

È un meccanismo di backpressure automatico. Non dobbiamo fare nulla - il kernel gestisce tutto.

**Codice:** Non facciamo niente di speciale, usiamo il behavior standard di fork() + pipe().

---

## 2️⃣ "Cosa succede se un comando in una pipe genera un segnale?"

**Domanda tricky:** Come fate a catturare il segnale del figlio?

**Risposta completa:**
Quando un processo figlio riceve un segnale e muore (es. Ctrl+C), il suo exit status contiene informazioni sul segnale.

```c
pid_t pid = fork();
if (pid == 0) {
    execve(cmd, ...);  // Figlio
} else {
    waitpid(pid, &status, 0);  // Padre aspetta
    
    if (WIFSIGNALED(status)) {
        int sig = WTERMSIG(status);
        // Il figlio è stato terminato dal segnale 'sig'
        shell->exit_code = 128 + sig;  // Bash convention
    }
}
```

Quindi se l'utente preme Ctrl+C durante una pipe, il processo figlio riceve SIGINT e muore. Noi leggiamo il suo status con `waitpid()` e sappiamo che è stato un segnale.

---

## 3️⃣ "Perché allocate memoria per le stringhe nei token quando potete usare puntatori diretti?"

**Domanda tricky:** Qual è il rischio di usare puntatori diretti?

**Risposta completa:**
Se usassimo puntatori diretti alla stringa originale di input:

```c
// SBAGLIATO:
t_token *token = malloc(sizeof(t_token));
token->value = input_string + offset;  // Puntatore diretto, non copia!
```

Problemi:
1. La stringa originale potrebbe venire modificata
2. La memoria potrebbe venire deallocata
3. Due token potrebbero avere puntatori overlappanti

**Soluzione: ft_strdup()**
```c
token->value = ft_strdup(input_string + offset);  // Copia la stringa
```

Ora ogni token ha la sua copia indipendente.

---

## 4️⃣ "Come gestite il timing di Ctrl+C proprio mentre readline ritorna?"

**Domanda tricky:** Race condition?

**Risposta completa:**
Se Ctrl+C viene premuto nel momento esatto in cui readline sta per ritornare (per esempio, l'utente ha appena premuto Enter), cosa succede?

**Comportamento:**
1. Se premuto PRIMA che readline ritorna: readline si interrompe, ritorna NULL (EOF), mostriamo nuovo prompt
2. Se premuto DURANTE readline: signal handler setta g_signal, readline continua, ritorna la linea, noi vediamo g_signal settato
3. Se premuto DOPO readline ritorna: il segnale è catturato dopo, vediamo g_signal settato nel prossimo ciclo

Non c'è race condition problematica perché:
- Siamo single-threaded (non c'è parallelismo reale)
- I segnali vengono consegnati comunque
- Verifichiamo g_signal dopo operazioni bloccanti

---

## 5️⃣ "Cosa accade se exportate una variabile con lo stesso nome due volte?"

**Domanda tricky:** Gestite il sovrascrivimento?

**Risposta completa:**
```bash
minishell$ export TEST=hello
minishell$ export TEST=world
minishell$ echo $TEST
world
```

Sì, gestiamo il sovrascrivimento. Quando exportate una variabile che esiste già:

```c
int export_var(char *var_name, char *var_value, t_shell *shell) {
    int idx = find_env_index(var_name, shell->envp);
    
    if (idx >= 0) {
        // Variabile esiste, la sovrascriviamo
        free(shell->envp[idx]);
        shell->envp[idx] = ft_strjoin(var_name, "=");
        shell->envp[idx] = ft_strjoin(shell->envp[idx], var_value);
    } else {
        // Variabile non esiste, l'aggiungiamo
        env_add(var_name, var_value, shell);
    }
}
```

---

## 6️⃣ "E se unsetate la stessa variabile due volte?"

**Domanda tricky:** Gestite l'errore?

**Risposta completa:**
```bash
minishell$ export TEST=hello
minishell$ unset TEST
minishell$ unset TEST
minishell$ echo $?
0
```

Non è un errore, simply non fa nulla. Se la variabile non esiste, unset non fa nulla e ritorna 0.

```c
int unset_var(char *var_name, t_shell *shell) {
    int idx = find_env_index(var_name, shell->envp);
    
    if (idx >= 0) {
        // Rimuoviamo la variabile
        // ... shift array
    }
    // Se idx < 0 (non trovata), non facciamo nulla
    
    return 0;  // Sempre successo
}
```

---

## 7️⃣ "Come evitate deadlock quando usate pipe?"

**Domanda tricky:** E se il buffer della pipe si riempie e nessuno legge?

**Risposta completa:**
```bash
cat file | wc
```

Scenari possibili:
1. **Buffer pipe pieno:** cat si blocca su write()
2. **Nessuno legge:** wc dovrebbe leggere da stdin (che è collegato a cat)

Questo NON è un deadlock perché:
- Il kernel gestisce automaticamente il blocking
- cat si blocca finché wc non legge
- wc legge, il buffer si libera, cat continua
- È tutto sequenziale, non c'è circolarità

Vero deadlock sarebbe: Processo A aspetta B che aspetta A.

**La nostra architettura è lineare (pipe è concatenazione)**, quindi impossibile deadlock.

---

## 8️⃣ "Cosa succede con il file descriptor 0, 1, 2 durante una redirection?"

**Domanda tricky:** Come evitate di perderli?

**Risposta completa:**
```bash
echo hello > /tmp/file
```

FD 0, 1, 2 sono stdin, stdout, stderr - critici!

**Processo:**
1. Salviamo stdout con: `int saved = dup(1);`
2. Apriamo il file: `int fd = open("/tmp/file", ...);`
3. Ridirezzioniamo: `dup2(fd, 1);`  // stdout ora punta al file
4. Eseguiamo il comando
5. Ripristiniamo: `dup2(saved, 1);`  // stdout torna originale
6. Puliamo: `close(fd); close(saved);`

dup() crea un nuovo file descriptor che punta allo stesso file. Per es:
- FD 1 (stdout) originale punta a /dev/tty
- `saved = dup(1)` crea FD 3 che punta anche a /dev/tty
- `dup2(file_fd, 1)` fa puntare FD 1 al file
- Successivamente `dup2(saved, 1)` ripristina FD 1 a /dev/tty

---

## 9️⃣ "E se un comando legge stdin da una pipe mentre sta riscrivendo?"

**Domanda tricky:** Race condition?

**Risposta completa:**
```bash
echo hello | tee /tmp/file | cat
```

Cosa succede:
1. echo scrive su pipe1_write
2. tee legge da pipe1_read E scrive su /tmp/file E su pipe2_write
3. cat legge da pipe2_read

Non c'è race condition perché:
- Ogni processo ha i suoi fd
- I fd della pipe sono sincronizzati dal kernel
- Non c'è accesso concorrente ai file (tee scrive sequenzialmente)

Il kernel gestisce automaticamente l'ordine.

---

## 🔟 "Come gestite `echo $?` subito dopo un comando che fallisce in una pipe?"

**Domanda tricky:** Quale exit code ritorna?

**Risposta completa:**
```bash
minishell$ /bin/ls /nonexistent | grep test
ls: cannot access '/nonexistent': No such file
minishell$ echo $?
2
```

Ritorniamo il codice di uscita dell'ULTIMO comando nella pipe.

In bash sarebbe:
```bash
echo ${PIPESTATUS[@]}  # 2 1 (ls fail con 2, grep niente da fare)
echo $?  # 1 (ultimo command - grep)
```

Ma bash riporta il codice dell'ultimo comando con `$?`, come noi.

```c
// In executor.c:
for (each cmd in pipeline) {
    fork() + execve(cmd);
    waitpid(..., &status);
    exit_code = WEXITSTATUS(status);  // Sovrascrivere ad ogni iterazione
}
// Alla fine, exit_code contiene il codice dell'ultimo comando
```

---

## 1️⃣1️⃣ "Usate getenv() o mantenete una copia dell'ambiente?"

**Domanda tricky:** Quale approccio è migliore?

**Risposta completa:**
Manteniamo una **copia dell'ambiente** in `shell->envp`.

**Perché non getenv()?**
- `getenv()` legge da `extern char **environ`
- Non possiamo modificare `environ` (è di sola lettura)
- Quando creiamo un nuovo processo con fork() + execve(), dobbiamo passare il nostro array modificato

**Come mantenete la copia?**
```c
// All'inizio:
shell->envp_copy = malloc_env_copy(extern_environ);

// Quando modificate una variabile (export):
modify(shell->envp_copy, "VAR", "value");

// Quando eseguite un comando:
execve(cmd, args, shell->envp_copy);  // Passa il nostro ambiente modificato
```

I processi figli erediteranno le modifiche che abbiamo fatto con export/unset.

---

## 1️⃣2️⃣ "Cosa succede se due comandi leggono/scrivono lo stesso file?"

**Domanda tricky:** Gestite il locking?

**Risposta completa:**
No, non gestite locking Unix-level (non è richiesto).

```bash
minishell$ echo hello > /tmp/file &
minishell$ echo world > /tmp/file &
```

Questi due comandi possono sovrascriversi a vicenda. Unix non lo previene per design.

Se volesse locking, bash dovrebbe usare `flock()` o `fcntl()`, che non implemente.

Per minishell è OK non gestire questo caso.

---

## 1️⃣3️⃣ "Come evitate buffer overflow nella vostra implementazione?"

**Domanda tricky:** Quali protezioni avete?

**Risposta completa:**
1. **Non usate strcpy()** - usate `ft_strcpy()` che controlla lunghezze
2. **Non usate gets()** - usate `readline()` che è sicuro
3. **Allocate dinamicamente** - non usate array fissi sulla stack
4. **Limiti dei token** - non c'è limite esplicito, ma readline gestisce
5. **Valgrind** - controlliamo overflow di heap

```c
// SBAGLIATO (possibile overflow):
char buffer[100];
strcpy(buffer, input);  // Cosa se input è > 100 byte?

// GIUSTO:
char *buffer = malloc(strlen(input) + 1);
ft_strcpy(buffer, input);  // Controlla lunghezze
```

---

## 1️⃣4️⃣ "Gestite variabili d'ambiente con valore vuoto?"

**Domanda tricky:** Come distinguete `VAR=` da `VAR`?

**Risposta completa:**
```bash
minishell$ export EMPTY=
minishell$ echo "|$EMPTY|"
||
minishell$ export NOVALUE
minishell$ echo "|$NOVALUE|"
||
```

In bash:
```bash
$ export EMPTY=
$ env | grep EMPTY
EMPTY=    # Valore vuoto
$ export NOVALUE
$ env | grep NOVALUE
NOVALUE   # Senza = (bash distingue)
```

**Voi non distinguete**, che è una semplificazione accettabile.

Entrambi espandono a stringa vuota, che è quello che importa per il funzionamento.

---

## 1️⃣5️⃣ "Cosa succede se eseguite un comando binario che stampa su stderr?"

**Domanda tricky:** Come redirezionate stderr?

**Risposta completa:**
```bash
minishell$ /usr/bin/ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
```

Lo stderr (fd 2) va direttamente al terminale perché **non lo redirezzioniamo**.

Se l'utente vuol redirezionare stderr:
```bash
minishell$ /usr/bin/ls /nonexistent 2> /tmp/error.txt
minishell$ cat /tmp/error.txt
ls: cannot access '/nonexistent': No such file or directory
```

Ma minishell **non supporta `2>` perché non è richiesto dal progetto**.

Solo `<`, `>`, `>>`, `<<` sono richiesti.

---

## 1️⃣6️⃣ "Come gestite un input molto lungo, tipo 10000 caratteri?"

**Domanda tricky:** Quali sono i limiti?

**Risposta completa:**
`readline()` non ha limite teorico (alloca dinamicamente).

La vostra implementazione supporta linee arbitrariamente lunghe perché:
1. `readline()` usa malloc internamente
2. Il lexer processa token sequenzialmente
3. La memoria viene deallocata dopo l'esecuzione

Unici limiti:
- Memoria totale del sistema
- ARG_MAX (massimo totale dei parametri a execve, solitamente 128KB)

```bash
minishell$ python3 -c "print('x' * 100000)" | xargs echo
# Fallerà se la linea supera ARG_MAX
```

Ma questo è un limite del sistema, non della vostra shell.

---

## 1️⃣7️⃣ "E se un comando tenta di modificare l'ambiente (con setenv)?"

**Domanda tricky:** Funziona?

**Risposta completa:**
```bash
minishell$ /bin/bash -c 'export MYVAR=test'
minishell$ echo $MYVAR
(nulla)
```

Non funziona perché il figlio modifica il suo ambiente, non il nostro.

Se volete che `export` funzioni:
```bash
minishell$ export MYVAR=test
minishell$ echo $MYVAR
test
```

Deve essere eseguito nel main process, non in un figlio.

---

## 1️⃣8️⃣ "Come testare che non avete memory leak?"

**Domanda tricky:** Che tool usate?

**Risposta completa:**
```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --suppressions=minishell.supp \
         ./minishell
```

**Poi eseguite comandi:**
```
echo test
export VAR=hello
ls | grep mini
cat << EOF
test
EOF
exit
```

**Cercate:**
```
definitely lost: 0 bytes in 0 blocks
indirectly lost: 0 bytes in 0 blocks
ERROR SUMMARY: 0 errors from 0 contexts
```

**Se ci sono leak:**
1. Valgrind mostra dove è stato allocato
2. Valgrind mostra se potete raggiungere la memoria
3. Esaminare il codice di cleanup

---

## 1️⃣9️⃣ "Quali sono i vostri 3 bug più difficili da trovare?"

**Risposta suggerita:**

1. **Quote annidate** - Difficile capire che bisogna tracciare lo stato
2. **Heredoc senza delimitatore** - Crash perché non controllava NULL
3. **Export senza valore** - Non controllava se il valore era vuoto

---

## 2️⃣0️⃣ "Se poteste rifare il progetto, cosa fareste diversamente?"

**Risposta suggerita:**

1. **Norminette fin dall'inizio** - Così non avrei 30 file da fixare alla fine
2. **Unit test mentre implemento** - Invece di fare tutto e poi testare
3. **Architettura per gli alias** - Avere uno spazio nel design
4. **Distinguere variabili solo-shell da export** - Come bash, non è difficile
5. **PIPESTATUS** - Non è difficile, ma non l'ho fatto

---

## 🎯 CONSIGLIO FINALE

La cosa più importante: **siate autentici**. Se non sapete una risposta, è OK dirlo. Un buon correttore apprezzerà l'onestà più che una risposta falsa.

Se non ricordate il dettaglio esatto di come qualcosa funziona, potete sempre dire "posso controllare il codice un momento?" e il correttore permetterà.

**Siete preparati. Potete farcela.** 💪
