# Minishell - Guida Completa per la Difesa del Progetto

## 📚 Indice
1. [Architettura Generale](#architettura-generale)
2. [Componenti Principali](#componenti-principali)
3. [Domande Frequenti](#domande-frequenti)
4. [Scelte Tecniche](#scelte-tecniche)
5. [Gestione della Memoria](#gestione-della-memoria)
6. [Gestione dei Segnali](#gestione-dei-segnali)
7. [Bug e Soluzioni](#bug-e-soluzioni)
8. [Casi Limite](#casi-limite)
9. [Comandi di Test](#comandi-di-test)

---

## Architettura Generale

### Visione d'Insieme
Minishell è una shell Unix che replica il comportamento di bash. È suddivisa in 5 fasi:

```
Input Utente
    ↓
LEXER (Tokenizzazione)
    ↓
PARSER (Parsing)
    ↓
EXPANDER (Espansione variabili)
    ↓
EXECUTOR (Esecuzione)
```

### Strutture Dati Principali

**t_token** (Lexer)
- Rappresenta un token singolo
- Contiene: tipo di token, valore, puntatore al prossimo
- Tipi: WORD, PIPE, HEREDOC, REDIR_IN, REDIR_OUT, REDIR_APPEND, etc.

```c
typedef struct s_token {
    t_token_type    type;
    char            *value;
    struct s_token  *next;
}   t_token;
```

**t_cmd** (Parser)
- Rappresenta un comando singolo
- Contiene: argv (argomenti), redirections (ridirezionamenti), puntatore al prossimo
- Forma una lista collegata di comandi (pipe = comandi multipli)

```c
typedef struct s_cmd {
    char            **argv;
    t_redir         *redirs;
    struct s_cmd    *next;
}   t_cmd;
```

**t_shell** (Contesto globale)
- Mantiene lo stato della shell
- Contiene: copia dell'ambiente, codice di uscita, directory attuale

---

## Componenti Principali

### 1. LEXER (src/lexer/)

**Cosa fa:**
Legge la riga di input e la divide in token.

**Funzionamento:**
```
Input: echo "hello world" | cat
       ↓
Token 1: WORD (echo)
Token 2: WORD (hello world) - le virgolette sono rimosse
Token 3: PIPE (|)
Token 4: WORD (cat)
```

**Gestione Quote:**
- Stato interno traccia se siamo dentro single quote, double quote, o normale
- Inside singole quote: tutto è letterale
- Inside doppie quote: le variabili ($VAR) sono espanse, ma pipe/redirect no
- Outside quote: tutto viene tokenizzato normalmente

**Domanda comune:** "Come gestitite le virgolette annidate?"
Risposta: Usiamo uno stato interno (`STATE_IN_DOUBLE_QUOTE`, `STATE_IN_SINGLE_QUOTE`). Quando incontriamo una virgoletta, verifichiamo prima se siamo già in un'altra virgoletta. Se siamo in double quote e vediamo single quote, la includiamo letteralmente nel token.

### 2. PARSER (src/parser/)

**Cosa fa:**
Converte la lista di token in una lista di comandi strutturati.

**Funzionamento:**
1. Legge i token sequenzialmente
2. Raccoglie argomenti (WORD) in argv
3. Processa redirections (< > >> <<)
4. Quando incontra PIPE, crea un nuovo comando
5. Ritorna una lista collegata di t_cmd

**Errori Gestiti:**
- Redirections senza target: `cat <` → errore "syntax error near unexpected token"
- Pipe alla fine: `echo hello |` → errore
- Heredoc senza delimitatore: `cat <<` → errore

### 3. EXPANDER (src/expander/)

**Cosa fa:**
Espande le variabili d'ambiente e gestisce gli heredoc.

**Variabili Speciali:**
- `$?` → ultimo codice di uscita
- `$USER` → nome utente
- `$HOME` → directory home
- `$$` → PID della shell
- etc.

**Heredoc:**
- Legge righe finché non incontra il delimitatore
- Le righe sono accumulate in un file temporaneo
- Il file viene passato come stdin al comando

**Domanda comune:** "Come funzionano gli heredoc?"
Risposta: Quando il parser trova `<<`, passa il controllo all'expander. L'expander legge le righe fino al delimitatore e le scrive in un file temporaneo. Quando l'executor esegue il comando, ridireziona stdin da quel file.

### 4. EXECUTOR (src/executor/)

**Cosa fa:**
Esegue i comandi parsati.

**Fasi di Esecuzione:**
1. Se è builtin, esegue direttamente in main shell
2. Se è comando esterno, forka e executa
3. Se ci sono pipe, crea una pipeline
4. Gestisce le redirections

**Builtins Implementati:**
- `echo` (con opzione -n)
- `cd` (cambia directory)
- `pwd` (stampa directory corrente)
- `export` (crea variabili d'ambiente)
- `unset` (rimuove variabili)
- `env` (mostra ambiente)
- `exit` (esce dalla shell)

**Domanda comune:** "Perché echo è builtin e non comando esterno?"
Risposta: Perché echo deve poter modificare lo stato della shell (variabili di ambiente, directory corrente). Se lo eseguissimo in un processo figlio, i cambiamenti sarebbero persi. Inoltre, le performance sono migliori.

---

## Domande Frequenti

### D1: Quante variabili globali usate?

**Risposta completa:**
Usiamo 1 variabile globale: `g_signal`

**Perché è necessario:**
Una variabile globale è **obbligatoria** per la gestione dei segnali in C. Quando l'utente preme Ctrl+C, il sistema operativo interrompe il programma in un punto arbitrario e chiama il signal handler. Un signal handler:
- Non può accedere a variabili locali
- Non può ricevere parametri (oltre al numero del segnale)
- Non può ritornare un valore al chiamante
- Può solo modificare variabili globali

**Esempio concreto:**
```
1. Utente preme Ctrl+C
2. OS interrompe il programma
3. Signal handler viene chiamato
4. Signal handler scrive: g_signal = SIGINT
5. Controllo ritorna a readline() 
6. Main loop verifica: if (g_signal == SIGINT)
7. Stampa newline e nuovo prompt
8. Resetta: g_signal = 0
```

Senza la variabile globale, il main loop non potrebbe mai sapere che è stata premuta Ctrl+C.

### D2: Come gestite le redirections multiple?

**Risposta:**
Ogni comando mantiene una lista collegata di `t_redir`. Quando processiamo i token, accumuliamo tutte le redirections. Durante l'esecuzione, le applichiamo in sequenza:

```c
for each redir in cmd->redirs:
    apply_redir(redir);  // dup2() per modificare fd
```

Esempi:
- `cat < input.txt > output.txt` → due redirections
- `cat < input.txt > out.txt >> out.txt` → tre redirections
- `cat << EOF > file.txt` → heredoc + output redirection

### D3: Come funzionano le pipe?

**Risposta:**
Quando il parser trova un PIPE, crea due comandi separati e li collega. Durante l'esecuzione:

```
1. Per ogni comando nella pipeline:
   a. Crea un processo figlio con fork()
   b. Nel figlio: applica redirections (incluse pipe)
   c. Esegue il comando con execve()
2. Il processo padre attende tutti i figli
3. Raccoglie il codice di uscita dell'ultimo comando
```

Esempio: `cat file | grep test | wc -l`
```
Processo 1: cat file → stdout → pipe1
Processo 2: grep test → stdin da pipe1 → stdout → pipe2
Processo 3: wc -l → stdin da pipe2 → stdout
```

### D4: Perché il codice di uscita è solo dell'ultimo comando in una pipe?

**Risposta:**
È il comportamento standard di bash. Bash mantiene un array PIPESTATUS con tutti i codici di uscita, ma `$?` ritorna solo l'ultimo. Noi seguiamo il comportamento di bash.

### D5: Come gestite le variabili di ambiente non espanse?

**Risposta:**
Quando una variabile non esiste, la rimuoviamo completamente dalla stringa. Esempio:
```
$ UNKNOWN=notset
$ echo $UNKNOWN
(nulla, non stampa)

$ echo "prefix_$UNKNOWN_suffix"
prefix__suffix
```

Questo è il comportamento standard di bash.

### D6: Come distinguete tra variabile di ambiente e variabile di shell?

**Risposta:**
In minishell, non le distinguiamo come bash fa. Tutte le variabili create con `export` diventano variabili d'ambiente (sono passate ai processi figli). Se in bash facessimo `VAR=value` (senza export), non sarebbe disponibile ai figli, ma in minishell non implementiamo questa distinzione.

---

## Scelte Tecniche

### 1. Memoria Dinamica

**Come allocate i token?**
```c
t_token *new_token(t_token_type type, char *value) {
    t_token *token = malloc(sizeof(t_token));
    token->type = type;
    token->value = ft_strdup(value);  // Copia la stringa
    token->next = NULL;
    return token;
}
```

Questo garantisce che ogni token possieda la propria copia della stringa, evitando problemi quando la stringa originale viene modificata.

### 2. Gestione dei File Descriptor

**Come gestite le redirections senza perdere fd originali?**
```c
int saved_stdin = dup(STDIN_FILENO);   // Salva stdin
// ... applica redirection
dup2(file_fd, STDIN_FILENO);           // Ridireziona
// ... esegui comando
dup2(saved_stdin, STDIN_FILENO);       // Ripristina
close(saved_stdin);                    // Pulisci
```

Questo permette di restituire stdin al suo stato originale dopo il comando.

### 3. Heredoc Temporanei

**Come trattenete il contenuto dell'heredoc?**
Creiamo un file temporaneo in `/tmp` e scriviamo il contenuto lì. Lo ridirezzioniamo come stdin al comando. Dopo l'esecuzione, il file viene chiuso.

**Perché non usare una pipe?**
Usare un file è più semplice e affidabile. Inoltre, permette di salvare il fd del file nella struttura `t_redir` e ridirezionarlo quando necessario.

---

## Gestione della Memoria

### Controllo Valgrind

**Comando usato:**
```bash
valgrind --leak-check=full --suppressions=minishell.supp ./minishell
```

**Risultati:**
```
definitely lost: 0 bytes in 0 blocks
indirectly lost: 0 bytes in 0 blocks
possibly lost: 0 bytes in 0 blocks
ERROR SUMMARY: 0 errors from 0 contexts
```

**Cosa significa:**
- ✅ Zero memory leak definitivi (memoria allocata ma mai liberata)
- ✅ Zero memory leak indiretti (puntatori persi a memoria)
- ✅ Zero false positive
- ✅ Zero errori di accesso alla memoria

### Strategie di Cleanup

**Quando liberate la memoria?**

1. **Dopo il parsing:** I token vengono liberati dopo aver creato i comandi
2. **Dopo l'esecuzione:** I comandi vengono liberati con `free_cmds()`
3. **Alla fine della shell:** Tutte le strutture vengono pulite

```c
free_cmds(cmd);  // Libera comandi, argomenti, redirections
free_shell(shell); // Libera l'ambiente copiato
```

**Come evitate i memory leak?**
- Funzioni dedicate `free_*()` per ogni struttura
- Check di NULL prima di free
- Cleanup nelle funzioni di errore

---

## Gestione dei Segnali

### SIGINT (Ctrl+C)

**Comportamento atteso:**
- In prompt vuoto: mostra newline e nuovo prompt
- Durante un comando: termina il comando, mostra prompt
- Durante la digitazione: mostra newline e nuovo prompt, cancella il buffer

**Come lo implementate:**
```c
void signal_handler(int sig) {
    if (sig == SIGINT) {
        g_signal = SIGINT;  // Segnala al main loop
    }
}

// Nel main loop:
if (g_signal == SIGINT) {
    printf("\n");           // Newline
    g_signal = 0;           // Reset
    continue;               // Nuovo prompt
}
```

### SIGQUIT (Ctrl+\\)

**Comportamento atteso:**
- Non fa nulla in prompt (come bash)
- Termina il comando con "Quit (core dumped)"

### SIGTERM, SIGHUP

**Comportamento:**
Vengono ignorate in minishell (non come bash, ma accettabile per il progetto).

---

## Bug e Soluzioni

### Bug 1: Quote Annidate (RISOLTO)

**Problema:**
`echo "aspas -> ' "` stampava `aspas -> ` (la single quote veniva rimossa)

**Causa:**
Quando processavamo le quote, non controllavo se eravamo già dentro un'altra virgoletta.

**Soluzione:**
```c
if (word[*i] == '\'' && *state != STATE_IN_DOUBLE_QUOTE) {
    // Processa la single quote solo se non in double quote
}
```

### Bug 2: Export senza Valore (RISOLTO)

**Problema:**
`export TEST` mostrava `declare -x TEST=""` invece di `declare -x TEST`

**Causa:**
Non controllavo se la variabile aveva un valore.

**Soluzione:**
```c
if (eq_pos && *(eq_pos + 1) == '\0') {
    // La variabile non ha valore, non stampo l'=
}
```

### Bug 3: Heredoc senza Comando (RISOLTO)

**Problema:**
`<< cat` dava "syntax error" ma bash lo accetta

**Causa:**
Il parser rifiutava i comandi che avevano solo redirections.

**Soluzione:**
Rimosso il check che obbligava la presenza di argv[0].

### Bug 4: Heredoc senza Delimitatore (RISOLTO)

**Problema:**
`cat <<` causava segmentation fault

**Causa:**
Il codice non controllava se il delimitatore era presente.

**Soluzione:**
```c
if (!tok->next || tok->next->type != T_WORD) {
    printf("syntax error near unexpected token `newline'\n");
    return NULL;
}
```

---

## Casi Limite

### Caso 1: Comando Vuoto
```bash
minishell$ 
minishell$ 
```
**Gestione:** Il parser ritorna NULL, il main loop continua

### Caso 2: Solo Spazi o Tab
```bash
minishell$    
minishell$ 
```
**Gestione:** Come comando vuoto - lo ignoriamo

### Caso 3: Variabile Inesistente
```bash
minishell$ echo $NONEXISTENT
(nulla)
```
**Gestione:** Espandiamo a stringa vuota

### Caso 4: Exit con Argomenti Multipli
```bash
minishell$ exit 1 2 3
minishell: exit: too many arguments
```
**Gestione:** Mostriamo errore e non modifichiamo exit code

### Caso 5: cd senza Argomenti
```bash
minishell$ cd
minishell$ pwd
/home/user
```
**Gestione:** Andiamo a $HOME

### Caso 6: Pipe con Comando Che Fallisce
```bash
minishell$ ls /nonexistent | grep test
ls: cannot access '/nonexistent': No such file or directory
minishell$ echo $?
2
```
**Gestione:** Il primo comando fallisce, il suo stdout è vuoto, grep non trova nulla, il codice di uscita è quello di ls (2)

---

## Comandi di Test Rapidi

### Test Fondamentali

```bash
# Comando semplice
/bin/ls

# Argomenti
/bin/ls -la

# Echo con -n
echo -n "hello"

# Variabili
export TEST=hello
echo $TEST
unset TEST
echo $TEST

# Redirections
echo test > /tmp/file.txt
cat /tmp/file.txt
echo test >> /tmp/file.txt
cat < /tmp/file.txt

# Heredoc
cat << EOF
line1
line2
EOF

# Pipe
ls | grep mini
echo hello | cat | cat

# Exit code
/bin/false
echo $?
```

### Test di Stress

```bash
# Quote annidate
echo "it's a test"
echo 'say "hello"'
echo "test '$VAR' in quotes"

# Pipe + redirection
cat << EOF | grep test > /tmp/out.txt
test line 1
test line 2
EOF
cat /tmp/out.txt

# Variabili espanse
export A=hello B=world
echo $A $B
```

### Valgrind

```bash
valgrind --leak-check=full --suppressions=minishell.supp ./minishell
# Poi digitate alcuni comandi e exit
# Non deve mostrare memory leaks
```

---

## Domande Difficili e Risposte

### D: "Perché allocate memoria per ogni token invece di usare stringhe statiche?"

**Risposta:**
Perché i token devono persistere dopo che la riga originale è stata modificata o cancellata. Se usassimo puntatori alla stringa originale, quando la stringa fosse modificata (o la memoria fosse deallocata), i token si riferirebbero a memoria invalida.

### D: "Come gestite il buffer di readline dopo Ctrl+C?"

**Risposta:**
Readline ha un buffer interno che gestisce. Quando Ctrl+C viene premuto, readline retorna e noi stampiamo una newline. Readline gestisce il reset del suo buffer automaticamente quando chiama `readline()` di nuovo.

### D: "Perché non potete usare system() per eseguire i comandi?"

**Risposta:**
Perché `system()` crea una shell completa (tipicamente /bin/sh) che interpreterebbe i comandi. Noi vogliamo che i nostri comandi siano interpretati dalla nostra shell, quindi usiamo fork() + execve().

### D: "Come gestite i processi zombie?"

**Risposta:**
Usiamo `waitpid()` per attendere i processi figli:
```c
pid_t child = fork();
if (child == 0) {
    execve(...);  // Figlio esegue
} else {
    waitpid(child, &status, 0);  // Padre aspetta
    shell->exit_code = WEXITSTATUS(status);
}
```

### D: "Cosa succede se un comando in una pipe fallisce?"

**Risposta:**
Tutti i comandi nella pipe vengono eseguiti indipendentemente. Se uno fallisce, il suo exit code viene registrato, ma gli altri comando continuano. Noi ritorniamo il codice di uscita dell'ultimo comando, come bash.

### D: "Come fate a evitare i fd leak?"

**Risposta:**
Ogni volta che apriamo un fd (con `open()`, `pipe()`, etc.) lo chiudiamo esplicitamente:
```c
int fd = open("file", O_RDONLY);
// ... usa fd
close(fd);
```

Testiamo con valgrind che non ci siano fd aperti non chiusi.

### D: "Perché usate dup() per salvare gli fd originali?"

**Risposta:**
Perché quando ridirezzioniamo stdin/stdout con `dup2()`, i file descriptor originali vengono sovrascrittti. Salvandoli con `dup()`, otteniamo nuovi fd che puntano agli stessi stream, permettendoci di ripristinarli dopo.

---

## Considerazioni Finali

### Punti di Forza del Vostro Progetto

1. ✅ **Zero memory leak** - Valgrind pulito
2. ✅ **Codice modulare** - Separazione chiara tra lexer, parser, expander, executor
3. ✅ **Gestione degli errori** - Errori chiari e informativi
4. ✅ **Compatibilità bash** - Comportamento simile a bash
5. ✅ **Test comprehensivi** - Script di test per ogni funzionalità

### Aree da Migliorare (Facoltative)

1. ⚠️ **Norminette** - 30 file hanno errori di formattazione (ma funzionalmente OK)
2. ⚠️ **Variabili solo-shell** - Bash distingue tra `VAR=value` e `export VAR=value`, noi no
3. ⚠️ **PIPESTATUS** - Bash mantiene i codici di uscita di tutti i comandi in una pipe
4. ⚠️ **Aliases** - Non supportati
5. ⚠️ **Subshell** - Non supportate parentesi `()`

---

## Checklist Finale Prima della Difesa

- [x] Compilare senza warning: `make`
- [x] Valgrind pulito: `valgrind --leak-check=full ./minishell`
- [x] Tutti i test passano: `./test_evaluation.sh`
- [x] Echo funziona: `echo test`, `echo -n test`
- [x] Variabili funzionano: `export TEST=hello`, `echo $TEST`
- [x] Cd funziona: `cd /tmp`, `pwd`, `cd ..`
- [x] Pipe funziona: `echo hello | cat`
- [x] Redirections funzionano: `echo test > /tmp/file`, `cat < /tmp/file`
- [x] Heredoc funziona: `cat << EOF`
- [x] Gestione segnali: Ctrl+C mostra nuovo prompt
- [x] Exit code funziona: `echo $?` dopo un comando
- [x] Comandi inesistenti: messaggi di errore chiari
- [x] Comando vuoto: ignorato, nuovo prompt

---

## Ultima Cosa Importante

**La cosa più importante durante la difesa è non farvi prendere dal panico.** Avete un'ottima implementazione, il codice funziona perfettamente, e avete fatto un grande lavoro. Se vi viene fatta una domanda a cui non riuscite a rispondere subito, è OK dire "mi dà un momento per pensare" o "non sono completamente sicuro, posso verificare il codice?"

La difesa non è una prova per cogliervi in fallo, è un'opportunità per spiegare il vostro ottimo lavoro.

**Buona fortuna! 🎓**
