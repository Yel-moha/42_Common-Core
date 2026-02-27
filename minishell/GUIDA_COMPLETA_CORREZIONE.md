# 📋 MINISHELL - GUIDA COMPLETA PER LA CORREZIONE

**Versione:** 1.0  
**Data:** 27 Febbraio 2026  
**Uso:** Questa guida contiene TUTTI i test e le domande per la correzione del progetto Minishell

---

## 📑 INDICE

1. [Preliminari e Setup](#preliminari-e-setup)
2. [Test Pratici Obbligatori](#test-pratici-obbligatori)
3. [Domande Teoriche Frequenti](#domande-teoriche-frequenti)
4. [Domande Teoriche Avanzate](#domande-teoriche-avanzate)
5. [Test di Robustezza](#test-di-robustezza)
6. [Valutazione Memoria (Valgrind)](#valutazione-memoria-valgrind)
7. [Checklist Finale](#checklist-finale)

---

## 1. PRELIMINARI E SETUP

### ✅ Verifica Iniziale

**1.1 Compilazione**
```bash
cd /path/to/minishell
make
```
- ✅ Compila senza errori?
- ✅ Compila senza warning?
- ✅ Eseguibile `minishell` creato?

**1.2 Norminette**
```bash
norminette includes/ src/ libft/
```
- ✅ Tutti i file seguono la norma 42?
- ⚠️ Se ci sono errori minori, sono accettabili se funzionalità OK

**1.3 Variabili Globali**
- ✅ Massimo 1 variabile globale permessa
- ✅ Chiedere: "Quante variabili globali usate e perché?"
- ✅ Risposta attesa: 1 variabile (`g_signal`) per gestione segnali

**1.4 Avvio della Shell**
```bash
./minishell
```
- ✅ Si avvia senza errori?
- ✅ Mostra un prompt?
- ✅ Non stampa messaggi strani?

---

## 2. TEST PRATICI OBBLIGATORI

### 🔵 2.1 Comandi Semplici

**Test 1: Comando Assoluto**
```bash
/bin/ls
```
- ✅ Esegue ls?
- ✅ Mostra i file della directory corrente?

**Test 2: Comando Vuoto**
```bash
[Premi solo Enter]
```
- ✅ Mostra un nuovo prompt?
- ✅ Non dà errori?

**Test 3: Solo Spazi/Tab**
```bash
    [Spazi]    [Tab]    
```
- ✅ Mostra un nuovo prompt?
- ✅ Non esegue nulla?

**Test 4: Comando con Path Relativo**
```bash
../../../bin/ls
```
- ✅ Funziona?

---

### 🔵 2.2 Argomenti

**Test 5: Un Argomento**
```bash
/bin/ls -l
```
- ✅ Esegue ls -l?

**Test 6: Più Argomenti**
```bash
/bin/echo hello world test
```
- ✅ Stampa: `hello world test`?

**Test 7: Argomenti con Spazi (tra virgolette)**
```bash
echo "hello world"
```
- ✅ Stampa: `hello world`?

---

### 🔵 2.3 Built-in: echo

**Test 8: echo Base**
```bash
echo hello
```
- ✅ Stampa: `hello`?

**Test 9: echo Senza Argomenti**
```bash
echo
```
- ✅ Stampa una riga vuota?

**Test 10: echo con -n**
```bash
echo -n hello
```
- ✅ Stampa `hello` senza newline?
- ✅ Il prompt appare sulla stessa riga?

**Test 11: echo con -n Multipli**
```bash
echo -n -n -n hello
```
- ✅ Stampa `hello` senza newline?

**Test 12: echo con -n Combinati**
```bash
echo -nnnn hello
```
- ✅ Stampa `hello` senza newline?

**Test 13: echo con Più Argomenti**
```bash
echo hello world "test 123"
```
- ✅ Stampa: `hello world test 123`?

---

### 🔵 2.4 Built-in: cd

**Test 14: cd Assoluto**
```bash
cd /tmp
pwd
```
- ✅ `pwd` mostra `/tmp`?

**Test 15: cd Relativo**
```bash
cd ..
pwd
```
- ✅ `pwd` mostra directory parent?

**Test 16: cd Senza Argomenti**
```bash
cd
pwd
```
- ✅ Va a $HOME?
- ✅ `pwd` mostra la home directory?

**Test 17: cd a Directory Inesistente**
```bash
cd /directory/che/non/esiste
```
- ✅ Mostra messaggio di errore?
- ✅ Non crasha?

**Test 18: cd con Punto**
```bash
cd .
pwd
```
- ✅ Rimane nella stessa directory?

---

### 🔵 2.5 Built-in: pwd

**Test 19: pwd Base**
```bash
pwd
```
- ✅ Mostra la directory corrente?

**Test 20: pwd Dopo cd**
```bash
cd /tmp
pwd
cd /home
pwd
```
- ✅ Mostra `/tmp` e poi `/home`?

---

### 🔵 2.6 Built-in: export

**Test 21: export Base**
```bash
export TEST=hello
echo $TEST
```
- ✅ Stampa `hello`?

**Test 22: export Visualizzazione**
```bash
export
```
- ✅ Mostra le variabili esportate?
- ✅ Formato: `declare -x VAR="value"`?

**Test 23: export Senza Valore**
```bash
export TEST
export | grep TEST
```
- ✅ Mostra `declare -x TEST` (senza valore)?

**Test 24: export Sovrascrittura**
```bash
export TEST=hello
export TEST=world
echo $TEST
```
- ✅ Stampa `world`?

**Test 25: export Più Variabili**
```bash
export A=1 B=2 C=3
echo $A $B $C
```
- ✅ Stampa `1 2 3`?

---

### 🔵 2.7 Built-in: unset

**Test 26: unset Base**
```bash
export TEST=hello
unset TEST
echo $TEST
```
- ✅ Non stampa nulla (variabile rimossa)?

**Test 27: unset Variabile Inesistente**
```bash
unset VAR_NON_ESISTENTE
echo $?
```
- ✅ Exit code è 0?
- ✅ Non dà errori?

**Test 28: unset PATH**
```bash
export MYPATH=$PATH
unset PATH
ls
export PATH=$MYPATH
```
- ✅ `ls` fallisce (comando non trovato)?
- ✅ Dopo ripristino, `ls` funziona?

---

### 🔵 2.8 Built-in: env

**Test 29: env Base**
```bash
env
```
- ✅ Mostra tutte le variabili d'ambiente?
- ✅ Formato corretto `VAR=value`?

**Test 30: env Dopo export**
```bash
export NEWVAR=test
env | grep NEWVAR
```
- ✅ Mostra `NEWVAR=test`?

---

### 🔵 2.9 Built-in: exit

**Test 31: exit Senza Argomenti**
```bash
exit
```
- ✅ Esce dalla shell?

**Test 32: exit con Codice**
```bash
exit 42
```
Poi in bash:
```bash
echo $?
```
- ✅ Exit code è 42?

**Test 33: exit con Più Argomenti**
```bash
exit 1 2 3
```
- ✅ Mostra errore "too many arguments"?
- ✅ NON esce dalla shell?

**Test 34: exit con Argomento Non Numerico**
```bash
exit hello
```
- ✅ Mostra errore "numeric argument required"?
- ✅ Esce con codice 2?

---

### 🔵 2.10 Variabile Speciale: $?

**Test 35: $? Dopo Comando Riuscito**
```bash
/bin/true
echo $?
```
- ✅ Stampa `0`?

**Test 36: $? Dopo Comando Fallito**
```bash
/bin/false
echo $?
```
- ✅ Stampa `1`?

**Test 37: $? Dopo ls su File Inesistente**
```bash
ls /file/inesistente
echo $?
```
- ✅ Stampa `2` (o altro codice non-zero)?

**Test 38: $? Concatenato**
```bash
echo Codice: $? Fine
```
- ✅ Stampa il codice correttamente integrato?

---

### 🔵 2.11 Espansione Variabili

**Test 39: Variabile Semplice**
```bash
export USER=tester
echo $USER
```
- ✅ Stampa `tester`?

**Test 40: Variabile in Mezzo a Testo**
```bash
export NAME=John
echo Hello $NAME, welcome!
```
- ✅ Stampa `Hello John, welcome!`?

**Test 41: Variabile Inesistente**
```bash
echo $VAR_NON_ESISTENTE
```
- ✅ Non stampa nulla (espansa a stringa vuota)?

**Test 42: Più Variabili**
```bash
export A=hello B=world
echo $A $B
```
- ✅ Stampa `hello world`?

---

### 🔵 2.12 Quote: Virgolette Doppie

**Test 43: Doppie Quote Base**
```bash
echo "hello world"
```
- ✅ Stampa `hello world`?

**Test 44: Spazi Multipli in Doppie Quote**
```bash
echo "hello    world"
```
- ✅ Preserva gli spazi multipli?

**Test 45: Variabile in Doppie Quote**
```bash
export NAME=Alice
echo "Hello $NAME"
```
- ✅ Stampa `Hello Alice` (variabile espansa)?

**Test 46: Caratteri Speciali in Doppie Quote**
```bash
echo "cat file.txt | grep test > output.txt"
```
- ✅ Stampa letteralmente (pipe e redirect non interpretati)?

---

### 🔵 2.13 Quote: Virgolette Singole

**Test 47: Singole Quote Base**
```bash
echo 'hello world'
```
- ✅ Stampa `hello world`?

**Test 48: Variabile in Singole Quote**
```bash
export NAME=Bob
echo '$NAME'
```
- ✅ Stampa letteralmente `$NAME` (NON espansa)?

**Test 49: Caratteri Speciali in Singole Quote**
```bash
echo 'cat | grep | > < >> <<'
```
- ✅ Stampa letteralmente?

---

### 🔵 2.14 Quote: Nested (Annidate)

**Test 50: Singole in Doppie**
```bash
echo "It's a test"
```
- ✅ Stampa `It's a test`?

**Test 51: Doppie in Singole**
```bash
echo 'He said "hello"'
```
- ✅ Stampa `He said "hello"`?

---

### 🔵 2.15 Redirections: Output (>)

**Test 52: Redirect Output Semplice**
```bash
echo hello > /tmp/test_output.txt
cat /tmp/test_output.txt
```
- ✅ File contiene `hello`?

**Test 53: Redirect Output Sovrascrive**
```bash
echo first > /tmp/test_overwrite.txt
echo second > /tmp/test_overwrite.txt
cat /tmp/test_overwrite.txt
```
- ✅ File contiene solo `second`?

---

### 🔵 2.16 Redirections: Append (>>)

**Test 54: Redirect Append**
```bash
echo first > /tmp/test_append.txt
echo second >> /tmp/test_append.txt
cat /tmp/test_append.txt
```
- ✅ File contiene `first` e `second` (due righe)?

---

### 🔵 2.17 Redirections: Input (<)

**Test 55: Redirect Input**
```bash
echo "test content" > /tmp/test_input.txt
cat < /tmp/test_input.txt
```
- ✅ Stampa `test content`?

**Test 56: Redirect Input con wc**
```bash
echo -e "line1\nline2\nline3" > /tmp/test_wc.txt
wc -l < /tmp/test_wc.txt
```
- ✅ Mostra `3`?

---

### 🔵 2.18 Redirections: Heredoc (<<)

**Test 57: Heredoc Base**
```bash
cat << EOF
line 1
line 2
line 3
EOF
```
- ✅ Stampa le 3 righe?

**Test 58: Heredoc con Variabile**
```bash
export NAME=John
cat << EOF
Hello $NAME
EOF
```
- ✅ Stampa `Hello John` (variabile espansa)?

**Test 59: Heredoc Non Aggiunge a History**
- ✅ Premere freccia su dopo heredoc non mostra le righe dell'heredoc?

---

### 🔵 2.19 Redirections: Multiple

**Test 60: Input + Output**
```bash
echo "content" > /tmp/test_io.txt
cat < /tmp/test_io.txt > /tmp/test_io_out.txt
cat /tmp/test_io_out.txt
```
- ✅ Mostra `content`?

**Test 61: Redirect Multipli sullo Stesso FD**
```bash
echo hello > /tmp/test1.txt > /tmp/test2.txt
cat /tmp/test1.txt
cat /tmp/test2.txt
```
- ✅ Solo `test2.txt` contiene `hello`?
- ✅ `test1.txt` è vuoto o non esiste?

---

### 🔵 2.20 Pipes: Singola Pipe

**Test 62: Pipe Base**
```bash
echo hello | cat
```
- ✅ Stampa `hello`?

**Test 63: Pipe con Filtro**
```bash
ls | grep mini
```
- ✅ Mostra solo file/directory con "mini" nel nome?

**Test 64: Pipe con wc**
```bash
echo -e "line1\nline2\nline3" | wc -l
```
- ✅ Mostra `3`?

---

### 🔵 2.21 Pipes: Multiple

**Test 65: Due Pipe**
```bash
echo hello | cat | cat
```
- ✅ Stampa `hello`?

**Test 66: Tre Pipe**
```bash
ls -l | grep mini | wc -l
```
- ✅ Mostra il conteggio corretto?

---

### 🔵 2.22 Pipes + Redirections

**Test 67: Pipe + Output Redirect**
```bash
echo hello | cat > /tmp/test_pipe_out.txt
cat /tmp/test_pipe_out.txt
```
- ✅ File contiene `hello`?

**Test 68: Heredoc + Pipe**
```bash
cat << EOF | grep test
test line
other line
EOF
```
- ✅ Mostra solo `test line`?

---

### 🔵 2.23 PATH e Comandi

**Test 69: Comando Senza Path**
```bash
ls
echo
cat /etc/hostname
```
- ✅ Tutti i comandi funzionano?

**Test 70: Comando Dopo unset PATH**
```bash
unset PATH
ls
```
- ✅ Mostra errore "command not found"?

**Test 71: Ripristino PATH**
```bash
export OLDPATH=$PATH
unset PATH
export PATH=$OLDPATH
ls
```
- ✅ `ls` funziona dopo ripristino?

---

### 🔵 2.24 Segnali (Test Manuali - IMPORTANTE)

⚠️ **NOTA:** Questi test DEVONO essere eseguiti interattivamente, NON in uno script.

**Test 72: Ctrl+C su Prompt Vuoto**
```bash
[Premi Ctrl+C]
```
- ✅ Mostra un nuovo prompt su nuova riga?
- ✅ Exit code ($?) è 130?

**Test 73: Ctrl+\ su Prompt Vuoto**
```bash
[Premi Ctrl+\]
```
- ✅ Non fa nulla (come bash)?

**Test 74: Ctrl+D su Prompt Vuoto**
```bash
[Premi Ctrl+D]
```
- ✅ Esce dalla shell (come exit)?

**Test 75: Ctrl+C Dopo aver Digitato**
```bash
[Digita: echo hello]
[NON premere Enter]
[Premi Ctrl+C]
```
- ✅ Mostra nuovo prompt?
- ✅ Cancella il buffer digitato?

**Test 76: Ctrl+D Dopo aver Digitato**
```bash
[Digita: echo hello]
[Premi Ctrl+D]
```
- ✅ Non fa nulla (come bash)?

**Test 77: Ctrl+C Durante cat**
```bash
cat
[Premi Ctrl+C]
```
- ✅ Termina cat?
- ✅ Mostra nuovo prompt?

**Test 78: Ctrl+\ Durante cat**
```bash
cat
[Premi Ctrl+\]
```
- ✅ Termina cat con "Quit (core dumped)"?

**Test 79: Ctrl+D Durante cat**
```bash
cat
[Digita qualcosa]
[Premi Ctrl+D]
```
- ✅ cat stampa quello che hai digitato e termina?

**Test 80: Ctrl+C Durante grep**
```bash
grep test
[Premi Ctrl+C]
```
- ✅ Termina grep?
- ✅ Mostra nuovo prompt?

---

## 3. DOMANDE TEORICHE FREQUENTI

### 🟢 Q1: Quante variabili globali usate e perché?

**Risposta Attesa:**
> Usiamo **1 variabile globale**: `g_signal`
> 
> **Motivazione:** Le variabili globali sono necessarie per la gestione dei segnali in C. Quando un signal handler viene chiamato dal sistema operativo:
> - Non può accedere a variabili locali
> - Non può ricevere parametri personalizzati (solo il signal number)
> - Non può ritornare valori al chiamante
> - Può solo modificare variabili globali volatili
> 
> `g_signal` viene usato per comunicare tra il signal handler e il main loop:
> 1. Utente preme Ctrl+C
> 2. Signal handler setta `g_signal = SIGINT`
> 3. Main loop legge `g_signal` e agisce di conseguenza
> 4. Exit code viene impostato a 130 (128 + SIGINT)

**✅ Verificare:** Mostrare dove è dichiarata la variabile globale nel codice

---

### 🟢 Q2: Spiegate l'architettura generale di Minishell

**Risposta Attesa:**
> Minishell è diviso in **5 fasi principali**:
> 
> 1. **LEXER (Tokenizzazione)**
>    - Legge l'input utente
>    - Divide in token (WORD, PIPE, REDIR, etc.)
>    - Gestisce quote e caratteri speciali
> 
> 2. **PARSER (Parsing)**
>    - Converte token in comandi strutturati
>    - Crea lista collegata di `t_cmd`
>    - Raccoglie argomenti e redirections
> 
> 3. **EXPANDER (Espansione)**
>    - Espande variabili d'ambiente ($VAR, $?)
>    - Gestisce heredoc
>    - Sostituisce variabili con i loro valori
> 
> 4. **EXECUTOR (Esecuzione)**
>    - Esegue i comandi (builtin o esterni)
>    - Gestisce pipe e fork
>    - Applica redirections
> 
> 5. **CLEANUP**
>    - Libera memoria allocata
>    - Chiude file descriptor
>    - Prepara per il prossimo comando

**✅ Verificare:** Chiedere di mostrare le directory corrispondenti nel codice

---

### 🟢 Q3: Quali sono le strutture dati principali?

**Risposta Attesa:**
> **t_token** (Lexer)
> ```c
> typedef struct s_token {
>     t_token_type    type;      // WORD, PIPE, REDIR_IN, etc.
>     char            *value;     // Contenuto del token
>     struct s_token  *next;      // Lista collegata
> } t_token;
> ```
> 
> **t_cmd** (Parser)
> ```c
> typedef struct s_cmd {
>     char            **argv;     // Argomenti del comando
>     t_redir         *redirs;    // Lista di redirections
>     struct s_cmd    *next;      // Prossimo comando (pipe)
> } t_cmd;
> ```
> 
> **t_shell** (Contesto globale)
> ```c
> typedef struct s_shell {
>     char    **envp;             // Copia dell'ambiente
>     int     exit_code;          // Ultimo exit code
>     char    *cwd;               // Directory corrente
> } t_shell;
> ```

**✅ Verificare:** Chiedere di mostrare le definizioni nel file header

---

### 🟢 Q4: Come funziona il Lexer?

**Risposta Attesa:**
> Il Lexer legge l'input carattere per carattere e:
> 
> 1. **Gestisce Stati:**
>    - `STATE_NORMAL`: parsing normale
>    - `STATE_IN_SINGLE_QUOTE`: dentro apici singoli
>    - `STATE_IN_DOUBLE_QUOTE`: dentro apici doppi
> 
> 2. **Identifica Token:**
>    - Spazi/tab → separatori
>    - `|` → PIPE
>    - `<` → REDIR_IN
>    - `>` → REDIR_OUT
>    - `>>` → REDIR_APPEND
>    - `<<` → HEREDOC
>    - Altro → WORD
> 
> 3. **Quote:**
>    - Single quote: tutto letterale (anche $VAR)
>    - Double quote: espansione variabili, ma non pipe/redirect
> 
> **Esempio:**
> ```
> Input: echo "hello world" | cat
> 
> Token 1: WORD (echo)
> Token 2: WORD (hello world)  // quote rimosse
> Token 3: PIPE (|)
> Token 4: WORD (cat)
> ```

**✅ Verificare:** Chiedere di tracciare un esempio manualmente

---

### 🟢 Q5: Come funziona il Parser?

**Risposta Attesa:**
> Il Parser converte i token in comandi eseguibili:
> 
> 1. **Legge token sequenzialmente**
> 2. **Accumula argomenti:**
>    - WORD → aggiunge ad argv[]
> 3. **Processa redirections:**
>    - `<`, `>`, `>>`, `<<` → crea t_redir
> 4. **Separa comandi:**
>    - PIPE → crea nuovo t_cmd, collega con `next`
> 
> **Errori Sintattici Gestiti:**
> - Pipe all'inizio: `| echo`
> - Pipe alla fine: `echo |`
> - Redirect senza target: `cat <`
> - Doppia pipe: `cat || ls`
> 
> **Esempio:**
> ```
> Input: cat < file.txt | grep test
> 
> CMD 1:
>   argv: ["cat"]
>   redirs: [IN: file.txt]
>   next → CMD 2
> 
> CMD 2:
>   argv: ["grep", "test"]
>   redirs: NULL
>   next → NULL
> ```

**✅ Verificare:** Mostrare la funzione principale del parser

---

### 🟢 Q6: Come funziona l'Expander?

**Risposta Attesa:**
> L'Expander gestisce:
> 
> 1. **Espansione Variabili:**
>    - `$VAR` → cerca in `envp` e sostituisce con valore
>    - `$?` → sostituisce con ultimo exit code
>    - `$USER`, `$HOME`, etc. → variabili d'ambiente
> 
> 2. **Variabili Inesistenti:**
>    - `$NONEXIST` → espanso a stringa vuota
> 
> 3. **Quote:**
>    - In double quote: espande variabili
>    - In single quote: NON espande (letterale)
> 
> 4. **Heredoc:**
>    - Legge righe fino al delimitatore
>    - Espande variabili nelle righe
>    - Scrive in file temporaneo
>    - Ridireziona stdin da file
> 
> **Esempio:**
> ```bash
> export NAME=Alice
> echo "Hello $NAME"  →  "Hello Alice"
> echo '$NAME'        →  "$NAME"
> echo $NONE          →  ""
> ```

**✅ Verificare:** Testare una variabile non esistente

---

### 🟢 Q7: Come funziona l'Executor?

**Risposta Attesa:**
> L'Executor distingue tra:
> 
> **1. Builtin (in processo padre):**
> - `cd`, `export`, `unset`, `exit`
> - Devono modificare lo stato della shell
> - Eseguiti direttamente senza fork
> 
> **2. Comandi Esterni (fork + exec):**
> ```c
> pid = fork();
> if (pid == 0) {
>     // Processo figlio
>     apply_redirections(cmd->redirs);
>     execve(cmd->argv[0], cmd->argv, envp);
> } else {
>     // Processo padre
>     waitpid(pid, &status, 0);
>     exit_code = WEXITSTATUS(status);
> }
> ```
> 
> **3. Pipeline (più fork):**
> - Crea pipe per ogni comando
> - Fork per ogni comando
> - Collega stdin/stdout con dup2()
> - Attende tutti i processi
> - Ritorna exit code dell'ultimo

**✅ Verificare:** Chiedere perché `cd` è builtin

---

### 🟢 Q8: Perché cd è un builtin?

**Risposta Attesa:**
> `cd` **DEVE** essere un builtin perché:
> 
> 1. **Modifica la directory del processo corrente**
> 2. Se fosse eseguito in un fork:
>    - Il figlio cambierebbe directory
>    - Il figlio morirebbe
>    - Il padre rimarrebbe nella directory originale
> 
> **Analogia:**
> ```bash
> # Se cd fosse esterno:
> fork()
>   └─ figlio: chdir("/tmp")  ← Cambia directory
>   └─ figlio: exit()          ← Muore
> padre: pwd  → ancora nella directory originale!
> ```
> 
> Stesso motivo per `export`, `unset`, `exit`.

**✅ Verificare:** Far ragionare lo studente sul ciclo di vita dei processi

---

### 🟢 Q9: Come gestite le pipe?

**Risposta Attesa:**
> **Pipeline con N comandi:**
> 
> 1. **Creare N-1 pipe** (per N comandi)
> 2. **Fork N volte** (un processo per comando)
> 3. **Collegare stdin/stdout:**
>    - Primo comando: stdin normale, stdout → pipe 1
>    - Comandi intermedi: stdin ← pipe i-1, stdout → pipe i
>    - Ultimo comando: stdin ← pipe N-1, stdout normale
> 4. **Chiudere tutti i fd non necessari**
> 5. **Padre attende tutti i figli**
> 6. **Ritorna exit code dell'ultimo comando**
> 
> **Esempio: cat file | grep test | wc -l**
> ```
> Pipe 1: [read_end_1, write_end_1]
> Pipe 2: [read_end_2, write_end_2]
> 
> Processo 1 (cat):
>   stdout → write_end_1
>   
> Processo 2 (grep):
>   stdin ← read_end_1
>   stdout → write_end_2
>   
> Processo 3 (wc):
>   stdin ← read_end_2
> ```

**✅ Verificare:** Disegnare il grafo delle pipe su carta

---

### 🟢 Q10: Come gestite le redirections?

**Risposta Attesa:**
> **Salvataggio e Ripristino:**
> ```c
> // 1. Salva fd originale
> int saved_stdout = dup(STDOUT_FILENO);
> 
> // 2. Apri file
> int fd = open("output.txt", O_WRONLY | O_CREAT, 0644);
> 
> // 3. Ridireziona
> dup2(fd, STDOUT_FILENO);  // stdout → file
> 
> // 4. Esegui comando
> execute_command();
> 
> // 5. Ripristina
> dup2(saved_stdout, STDOUT_FILENO);
> 
> // 6. Chiudi
> close(fd);
> close(saved_stdout);
> ```
> 
> **Redirections Multiple:**
> Le applichiamo in ordine sequenziale. L'ultima sovrascrive le precedenti sullo stesso fd.

**✅ Verificare:** Testare `echo hello > a.txt > b.txt`

---

### 🟢 Q11: Come funzionano gli heredoc?

**Risposta Attesa:**
> **Processo Heredoc:**
> 
> 1. **Parser** identifica `<<` e delimitatore (es. `EOF`)
> 2. **Expander** viene chiamato per processare l'heredoc:
>    ```c
>    while (line != delimiter) {
>        line = readline("> ");
>        expand_variables(line);  // Espande $VAR
>        write_to_temp_file(line);
>    }
>    ```
> 3. **File temporaneo** viene creato in `/tmp`
> 4. **Executor** ridireziona stdin dal file:
>    ```c
>    int fd = open(heredoc_file, O_RDONLY);
>    dup2(fd, STDIN_FILENO);
>    ```
> 5. Dopo exec, il file viene chiuso/eliminato
> 
> **Caratteristiche:**
> - Le righe dell'heredoc NON vanno nella history
> - Le variabili vengono espanse (come in double quote)
> - Il prompt durante heredoc è diverso (es. `> `)

**✅ Verificare:** Testare heredoc con variabile

---

### 🟢 Q12: Come gestite i segnali?

**Risposta Attesa:**
> **Setup Segnali:**
> ```c
> struct sigaction sa;
> sa.sa_handler = signal_handler;
> sigemptyset(&sa.sa_mask);
> sa.sa_flags = SA_RESTART;  // Riavvia syscall interrotte
> sigaction(SIGINT, &sa, NULL);  // Ctrl+C
> sigaction(SIGQUIT, &sa, NULL); // Ctrl+\
> ```
> 
> **Signal Handler:**
> ```c
> void signal_handler(int sig) {
>     if (sig == SIGINT) {
>         g_signal = SIGINT;
>         write(1, "\n", 1);
>         rl_on_new_line();
>         rl_replace_line("", 0);
>         rl_redisplay();
>     }
> }
> ```
> 
> **Main Loop:**
> ```c
> while (1) {
>     line = readline("minishell$ ");
>     
>     if (g_signal == SIGINT) {
>         shell->exit_code = 130;  // 128 + SIGINT
>         g_signal = 0;
>     }
>     
>     // ... processa comando
> }
> ```
> 
> **Comportamenti:**
> - **Ctrl+C:** Interrompe comando, mostra nuovo prompt, exit code 130
> - **Ctrl+\:** Durante comando → "Quit", altrimenti ignorato
> - **Ctrl+D:** EOF, equivale a `exit`

**✅ Verificare:** Testare i 3 segnali interattivamente

---

### 🟢 Q13: Come gestite la memoria?

**Risposta Attesa:**
> **Strategie di Cleanup:**
> 
> 1. **Dopo Lexer:**
>    ```c
>    free_tokens(token_list);  // Libera tutti i token
>    ```
> 
> 2. **Dopo Parser:**
>    ```c
>    free_cmds(cmd_list);  // Libera comandi, argv, redirs
>    ```
> 
> 3. **Funzioni Dedicate:**
>    ```c
>    void free_token_list(t_token *tok) {
>        while (tok) {
>            free(tok->value);
>            t_token *next = tok->next;
>            free(tok);
>            tok = next;
>        }
>    }
>    ```
> 
> 4. **Valgrind:**
>    ```bash
>    valgrind --leak-check=full \
>             --suppressions=minishell.supp \
>             ./minishell
>    ```
>    - Risultato atteso: **0 bytes lost**
> 
> 5. **Suppressions per Readline:**
>    - Readline alloca memoria interna che non libera
>    - File `.supp` dice a Valgrind di ignorare questi leak

**✅ Verificare:** Eseguire valgrind e mostrare risultati

---

### 🟢 Q14: Cosa sono le funzioni autorizzate e come le usate?

**Risposta Attesa:**
> **System Calls Principali:**
> 
> - **I/O:** `open()`, `close()`, `read()`, `write()`
> - **Processi:** `fork()`, `execve()`, `wait()`, `waitpid()`
> - **File Descriptors:** `dup()`, `dup2()`, `pipe()`
> - **Segnali:** `signal()`, `sigaction()`, `kill()`
> - **Directory:** `getcwd()`, `chdir()`
> - **Ambiente:** `getenv()` (ma manteniamo copia in `envp`)
> - **Memory:** `malloc()`, `free()`
> - **Stat:** `access()`, `stat()`, `lstat()`, `fstat()`
> - **Terminal:** `isatty()`, `ttyname()`, `ttyslot()`
> - **Altri:** `perror()`, `strerror()`, `errno`
> 
> **Readline Library:**
> - `readline()`: legge input con editing
> - `rl_on_new_line()`, `rl_replace_line()`, `rl_redisplay()`: gestione prompt
> - `add_history()`: aggiunge comando alla history
> - `rl_clear_history()`: pulisce history

**✅ Verificare:** Chiedere uso specifico di 2-3 funzioni

---

### 🟢 Q15: Perché mantenete una copia di envp invece di usare getenv()?

**Risposta Attesa:**
> **Motivazioni:**
> 
> 1. **Modificabilità:**
>    - `extern char **environ` è di sola lettura
>    - `export` e `unset` devono modificare l'ambiente
>    - Dobbiamo poter aggiungere/rimuovere/modificare variabili
> 
> 2. **Passaggio ai Figli:**
>    - `execve()` richiede un array di stringhe
>    - Dobbiamo passare il nostro ambiente modificato:
>      ```c
>      execve(path, argv, shell->envp);  // Nostro array
>      ```
> 
> 3. **Isolamento:**
>    - Le modifiche non affettano l'ambiente del processo padre
>    - Possiamo sperimentare senza rischi
> 
> **Implementazione:**
> ```c
> // All'inizio:
> shell->envp = copy_environment(envp);
> 
> // Export:
> add_to_envp(shell->envp, "VAR=value");
> 
> // Unset:
> remove_from_envp(shell->envp, "VAR");
> 
> // Exec:
> execve(cmd, args, shell->envp);  // Passa modifiche ai figli
> ```

**✅ Verificare:** Testare export e verificare che appaia in env

---

## 4. DOMANDE TEORICHE AVANZATE

### 🔴 Q16: Cosa succede se il buffer della pipe si riempie?

**Risposta Attesa:**
> **Meccanismo di Backpressure:**
> 
> Le pipe hanno un buffer limitato (tipicamente 64KB in Linux):
> 
> 1. **Produttore scrive velocemente:**
>    ```
>    yes | sleep 10
>    ```
> 
> 2. **Buffer si riempie:**
>    - `yes` continua a scrivere nella pipe
>    - Quando il buffer è pieno, `write()` si **blocca**
> 
> 3. **Consumatore legge:**
>    - `sleep` non legge per 10 secondi
>    - Quando `sleep` termina, la pipe si chiude
>    - `yes` riceve SIGPIPE e termina
> 
> **Conclusione:** Il kernel gestisce automaticamente il flow control. Non serve fare nulla nel nostro codice.

**✅ Verificare:** Testare `yes | head -5` e osservare che termina subito

---

### 🔴 Q17: Come evitate i file descriptor leak?

**Risposta Attesa:**
> **Strategia:**
> 
> 1. **Principio:** Ogni `open()`, `pipe()`, `dup()` deve avere un `close()`
> 
> 2. **Tracking:**
>    ```c
>    int fd = open("file", O_RDONLY);
>    if (fd < 0) {
>        perror("open");
>        return ERROR;
>    }
>    
>    // ... usa fd
>    
>    close(fd);  // SEMPRE chiudere
>    ```
> 
> 3. **Pipeline:**
>    ```c
>    pipe(pipefd);
>    if (fork() == 0) {
>        close(pipefd[0]);  // Chiudi read nel writer
>        dup2(pipefd[1], STDOUT);
>        close(pipefd[1]);  // Chiudi dopo dup2
>    } else {
>        close(pipefd[1]);  // Chiudi write nel reader
>        // ...
>        close(pipefd[0]);
>    }
>    ```
> 
> 4. **Valgrind può rilevare:**
>    ```bash
>    valgrind --track-fds=yes ./minishell
>    ```

**✅ Verificare:** Eseguire `lsof -p $$` dopo comandi

---

### 🔴 Q18: Cosa succede con redirections multiple sullo stesso fd?

**Risposta Attesa:**
> **Comportamento:**
> ```bash
> echo hello > a.txt > b.txt
> ```
> 
> 1. Parser crea due redirections per stdout:
>    - Redir 1: `>` → `a.txt`
>    - Redir 2: `>` → `b.txt`
> 
> 2. Executor applica in ordine:
>    ```c
>    fd1 = open("a.txt", O_WRONLY | O_CREAT);
>    dup2(fd1, STDOUT);  // stdout → a.txt
>    close(fd1);
>    
>    fd2 = open("b.txt", O_WRONLY | O_CREAT);
>    dup2(fd2, STDOUT);  // stdout → b.txt (sovrascrive!)
>    close(fd2);
>    ```
> 
> 3. **Risultato:**
>    - `a.txt`: vuoto (aperto ma mai scritto)
>    - `b.txt`: contiene `hello`
> 
> **Uguale a bash.**

**✅ Verificare:** Testare il comando e controllare i file

---

### 🔴 Q19: Come gestite i processi zombie?

**Risposta Attesa:**
> **Problema:**
> Quando un processo forka e il figlio muore, rimane come "zombie" finché il padre non chiama `wait()`.
> 
> **Soluzione:**
> ```c
> pid = fork();
> if (pid == 0) {
>     // Figlio esegue
>     execve(cmd, argv, envp);
>     exit(1);  // Se execve fallisce
> } else {
>     // Padre aspetta SEMPRE
>     waitpid(pid, &status, 0);  // Blocca fino a morte figlio
>     
>     if (WIFEXITED(status)) {
>         exit_code = WEXITSTATUS(status);
>     } else if (WIFSIGNALED(status)) {
>         exit_code = 128 + WTERMSIG(status);
>     }
> }
> ```
> 
> **Perché non ci sono zombie:**
> - Chiamiamo `waitpid()` per ogni fork
> - Il padre attende esplicitamente ogni figlio
> - I processi zombie vengono "reapati"

**✅ Verificare:** Eseguire `ps aux | grep minishell` e non vedere zombie

---

### 🔴 Q20: Cosa succede se un comando in una pipe riceve un segnale?

**Risposta Attesa:**
> **Scenario:**
> ```bash
> cat | cat | cat
> [Premi Ctrl+C]
> ```
> 
> 1. **SIGINT inviato al gruppo di processi:**
>    - Tutti i processi nella pipeline ricevono il segnale
> 
> 2. **Ogni processo muore:**
>    - `cat` 1 termina con SIGINT
>    - `cat` 2 termina con SIGINT (o SIGPIPE se sta leggendo)
>    - `cat` 3 termina con SIGINT
> 
> 3. **Padre raccoglie exit codes:**
>    ```c
>    for (each child) {
>        waitpid(pid, &status, 0);
>        if (WIFSIGNALED(status)) {
>            sig = WTERMSIG(status);  // SIGINT = 2
>            exit_code = 128 + sig;    // 130
>        }
>    }
>    ```
> 
> 4. **Exit code finale:** 130 (dall'ultimo processo)

**✅ Verificare:** Testare con Ctrl+C durante una pipeline

---

### 🔴 Q21: Come gestite quote nested complesse?

**Risposta Attesa:**
> **Esempi Complessi:**
> 
> 1. **Singole in Doppie:**
>    ```bash
>    echo "It's a 'nested' test"
>    ```
>    Output: `It's a 'nested' test`
>    - Le singole sono letterali dentro doppie
> 
> 2. **Doppie in Singole:**
>    ```bash
>    echo 'He said "hello"'
>    ```
>    Output: `He said "hello"`
>    - Le doppie sono letterali dentro singole
> 
> 3. **Consecutivi:**
>    ```bash
>    echo "hello"' world'"test"
>    ```
>    Output: `hello worldtest`
>    - Concatenazione di 3 token
> 
> **Implementazione:**
> ```c
> if (c == '\'' && state != IN_DOUBLE_QUOTE) {
>     // Gestisci single quote solo se non in double
> }
> if (c == '"' && state != IN_SINGLE_QUOTE) {
>     // Gestisci double quote solo se non in single
> }
> ```

**✅ Verificare:** Testare tutti gli esempi sopra

---

### 🔴 Q22: Perché allocate memoria per i token invece di usare puntatori?

**Risposta Attesa:**
> **Problema con Puntatori Diretti:**
> ```c
> // SBAGLIATO:
> char *input = readline("$ ");
> token->value = input + offset;  // Puntatore diretto!
> free(input);  // ERRORE: token->value ora invalido!
> ```
> 
> **Soluzione con Copia:**
> ```c
> // CORRETTO:
> char *input = readline("$ ");
> token->value = ft_strdup(input + offset);  // Copia
> free(input);  // OK: token ha la sua copia
> ```
> 
> **Vantaggi:**
> 1. **Indipendenza:** Token sopravvive alla stringa originale
> 2. **Sicurezza:** Nessun dangling pointer
> 3. **Memoria:** Ogni token padrone della sua memoria
> 
> **Svantaggio:** Più allocazioni, ma necessario per correttezza

**✅ Verificare:** Far ragionare sullo stack trace

---

### 🔴 Q23: Come gestite race conditions con i segnali?

**Risposta Attesa:**
> **Scenario Critico:**
> ```c
> line = readline("$ ");  // Bloccante
> // ← Ctrl+C premuto QUI
> if (line) {
>     process(line);
> }
> ```
> 
> **Non è una vera race condition perché:**
> 
> 1. **Single-threaded:**
>    - Non c'è parallelismo reale
>    - I segnali sono asincroni ma gestiti sequenzialmente
> 
> 2. **Signal Handler Breve:**
>    ```c
>    void handler(int sig) {
>        g_signal = sig;  // Atomo write
>        // Non facciamo altro di complesso
>    }
>    ```
> 
> 3. **Check Esplicito:**
>    ```c
>    line = readline("$ ");
>    if (g_signal) {
>        handle_signal();
>        g_signal = 0;
>    }
>    if (line) {
>        process(line);
>    }
>    ```
> 
> 4. **SA_RESTART:**
>    - Se segnale arriva durante syscall interrompibile
>    - La syscall viene riavviata automaticamente

**✅ Verificare:** Far ragionare sul modello di esecuzione

---

### 🔴 Q24: Cosa succede se exportate una variabile e poi la modificate?

**Risposta Attesa:**
> **Test:**
> ```bash
> export VAR=hello
> echo $VAR        # hello
> export VAR=world
> echo $VAR        # world
> ```
> 
> **Implementazione:**
> ```c
> int export_variable(char *name, char *value, t_shell *sh) {
>     int idx = find_in_env(name, sh->envp);
>     
>     if (idx >= 0) {
>         // Esiste: sovrascrivere
>         free(sh->envp[idx]);
>         sh->envp[idx] = create_env_string(name, value);
>     } else {
>         // Non esiste: aggiungere
>         sh->envp = add_to_env(sh->envp, name, value);
>     }
> }
> ```
> 
> **Memoria:**
> - La stringa vecchia viene liberata
> - Nuova stringa allocata
> - Nessun memory leak

**✅ Verificare:** Testare ed eseguire valgrind

---

### 🔴 Q25: Come gestite PATH con comandi inesistenti?

**Risposta Attesa:**
> **Processo di Ricerca:**
> 
> 1. **Se path assoluto o relativo:**
>    ```bash
>    /bin/ls    # Prova direttamente
>    ./script   # Prova direttamente
>    ```
> 
> 2. **Altrimenti, cerca in PATH:**
>    ```c
>    char *find_command(char *cmd, char **envp) {
>        if (cmd[0] == '/' || cmd[0] == '.') {
>            return ft_strdup(cmd);  // Path esplicito
>        }
>        
>        char *path = getenv_from_envp("PATH", envp);
>        char **dirs = ft_split(path, ':');
>        
>        for (int i = 0; dirs[i]; i++) {
>            char *full = ft_strjoin(dirs[i], "/", cmd);
>            if (access(full, X_OK) == 0) {
>                return full;  // Trovato!
>            }
>            free(full);
>        }
>        
>        return NULL;  // Non trovato
>    }
>    ```
> 
> 3. **Se non trovato:**
>    ```c
>    if (!cmd_path) {
>        printf("%s: command not found\n", cmd);
>        exit(127);
>    }
>    ```

**✅ Verificare:** Testare comando inesistente e verificare error message

---

## 5. TEST DI ROBUSTEZZA

### 🟣 Test di Errori Sintattici

**Test 81: Pipe all'inizio**
```bash
| echo hello
```
- ✅ Mostra "syntax error near unexpected token `|'"?

**Test 82: Pipe alla fine**
```bash
echo hello |
```
- ✅ Mostra "syntax error near unexpected token `newline'"?

**Test 83: Doppia Pipe**
```bash
cat || ls
```
- ✅ Mostra "syntax error near unexpected token `|'"?

**Test 84: Redirect senza Target**
```bash
cat <
```
- ✅ Mostra "syntax error near unexpected token `newline'"?

**Test 85: Doppio Redirect**
```bash
cat > > file
```
- ✅ Mostra errore appropriato?

**Test 86: Heredoc senza Delimitatore**
```bash
cat <<
```
- ✅ Mostra "syntax error near unexpected token `newline'"?

---

### 🟣 Test di Casi Limite

**Test 87: Comando Lunghissimo**
```bash
echo aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa...
[Ripeti per 1000+ caratteri]
```
- ✅ Gestisce senza crash?

**Test 88: Molte Pipe**
```bash
cat | cat | cat | cat | cat | cat | cat | cat | cat | cat
```
- ✅ Funziona?
- ✅ Exit code corretto?

**Test 89: Quote non Chiuse** (Bash le gestisce multilinea)
```bash
echo "hello
```
- ⚠️ Comportamento accettabile: errore o multilinea

**Test 90: Directory non Leggibile**
```bash
ls /root
```
- ✅ Mostra "Permission denied"?

**Test 91: File non Scrivibile**
```bash
echo test > /etc/readonly_file
```
- ✅ Mostra errore appropriato?

---

### 🟣 Test di Stress

**Test 92: Nested Minishell**
```bash
./minishell
./minishell
./minishell
exit
exit
exit
```
- ✅ Funziona su 3 livelli?

**Test 93: Molti Export**
```bash
export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8 I=9 J=10
env | wc -l
```
- ✅ Tutte le variabili create?

**Test 94: Pipeline con Errore**
```bash
ls /nonexistent | grep test | wc -l
echo $?
```
- ✅ Mostra output di ls (errore)?
- ✅ Exit code non-zero?

**Test 95: Heredoc Lungo**
```bash
cat << EOF
[100 righe di testo]
EOF
```
- ✅ Legge tutte le righe?

---

## 6. VALUTAZIONE MEMORIA (VALGRIND)

### 🔵 Setup Valgrind

**Comando Base:**
```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --suppressions=minishell.supp \
         ./minishell
```

**Dentro Minishell, testare:**
```bash
echo hello
export TEST=value
ls | grep mini
cat << EOF
test
EOF
exit
```

### 🔵 Risultati Attesi

**✅ Output Pulito:**
```
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: X allocs, X frees, Y bytes allocated

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts
```

**✅ Zero Leak:**
- `definitely lost: 0 bytes in 0 blocks`
- `indirectly lost: 0 bytes in 0 blocks`
- `possibly lost: 0 bytes in 0 blocks`

**⚠️ Note su Readline:**
- Readline può mostrare "still reachable" leak
- Questi sono OK e gestiti con suppressions
- Il file `.supp` dice a Valgrind di ignorarli

### 🔵 Test Specifici

**Test 96: Memory Leak su Loop**
```bash
# In minishell:
echo test
echo test  
echo test
[Ripeti 10 volte]
exit
```
- ✅ Ogni iterazione pulisce la memoria?

**Test 97: Memory Leak su Pipe**
```bash
ls | grep mini
ls | grep mini
[Ripeti 5 volte]
exit
```
- ✅ Nessun leak accumulato?

**Test 98: Memory Leak su Export**
```bash
export A=1
export A=2
export A=3
unset A
exit
```
- ✅ Memoria liberata correttamente?

---

## 7. CHECKLIST FINALE

### ✅ Funzionalità Obbligatorie

- [ ] **Comandi semplici** (`/bin/ls`, `echo hello`)
- [ ] **Argomenti** (con spazi, multipli)
- [ ] **Builtin: echo** (con -n, multipli -n)
- [ ] **Builtin: cd** (assoluto, relativo, senza args, errori)
- [ ] **Builtin: pwd** (mostra directory corrente)
- [ ] **Builtin: export** (crea, modifica, visualizza)
- [ ] **Builtin: unset** (rimuove variabili)
- [ ] **Builtin: env** (mostra ambiente)
- [ ] **Builtin: exit** (con/senza args, troppi args, non numerici)
- [ ] **Variabile $?** (exit code ultimo comando)
- [ ] **Espansione variabili** ($VAR, $USER, variabili inesistenti)
- [ ] **Quote singole** (tutto letterale, no espansione)
- [ ] **Quote doppie** (espansione variabili, no pipe/redirect)
- [ ] **Quote annidate** (singole in doppie, doppie in singole)
- [ ] **Redirects: >** (output, sovrascrive)
- [ ] **Redirects: >>** (append)
- [ ] **Redirects: <** (input)
- [ ] **Redirects: <<** (heredoc)
- [ ] **Redirects multipli** (stesso fd, diversi fd)
- [ ] **Pipe singola** (`cmd1 | cmd2`)
- [ ] **Pipe multiple** (`cmd1 | cmd2 | cmd3 | ...`)
- [ ] **Pipe + Redirects** (combinati)
- [ ] **PATH** (comandi senza path, ricerca in PATH)
- [ ] **Paths relativi** (`../../../bin/ls`)
- [ ] **Segnali: Ctrl+C** (interrompe, nuovo prompt, exit 130)
- [ ] **Segnali: Ctrl+\** (durante comando, ignorato su prompt)
- [ ] **Segnali: Ctrl+D** (EOF, equivale a exit)

### ✅ Qualità del Codice

- [ ] **Compilazione** (senza warning, senza errori)
- [ ] **Norminette** (42 norm, tolleranza minore se funzionale)
- [ ] **Variabili globali** (massimo 1, giustificata)
- [ ] **Memory management** (valgrind pulito, 0 leak)
- [ ] **Error handling** (messaggi chiari, no crash)
- [ ] **Code structure** (modulare, leggibile)
- [ ] **Comments** (dove necessario)

### ✅ Test Interattivi

- [ ] **Test su prompt vuoto** (Ctrl+C, Ctrl+D, Ctrl+\)
- [ ] **Test durante comando** (Ctrl+C su cat, grep)
- [ ] **Test dopo digitazione** (Ctrl+C cancella buffer)
- [ ] **Test heredoc** (signals durante heredoc)

### ✅ Domande Teoriche Verificate

- [ ] Variabili globali (quante, perché)
- [ ] Architettura (lexer, parser, expander, executor)
- [ ] Strutture dati (t_token, t_cmd, t_shell)
- [ ] Builtins (perché cd è builtin)
- [ ] Pipe (come funzionano, fd management)
- [ ] Redirections (dup/dup2, save/restore)
- [ ] Segnali (gestione, g_signal, exit codes)
- [ ] Memoria (free strategy, valgrind)
- [ ] Quote (nested, expansion rules)
- [ ] Fork/exec (processi, zombie, wait)

---

## 📊 GRADING RUBRIC

### Compilazione
- ✅ Compila: **5 punti**
- ❌ Non compila: **0 punti** (stop)

### Funzionalità Base (40 punti)
- Comandi semplici: **5 punti**
- Builtins (7 totali): **15 punti** (≈2 punti ciascuno)
- Quote (single, double, nested): **10 punti**
- Variables ($VAR, $?): **10 punti**

### Redirections (20 punti)
- `>`, `>>`, `<`: **10 punti**
- `<<` (heredoc): **10 punti**

### Pipes (20 punti)
- Pipe singola: **10 punti**
- Pipe multiple: **10 punti**

### Segnali (10 punti)
- Ctrl+C: **5 punti**
- Ctrl+\, Ctrl+D: **5 punti**

### Qualità (10 punti)
- Memory leaks: **5 punti**
- Error handling: **5 punti**

### **TOTALE: 100 punti**

**Passing Grade:** ≥ 80 punti

---

## 🎓 CONSIGLI PER LA DIFESA

### Per lo Studente

1. **Preparazione:**
   - Rivedi il codice prima della difesa
   - Esegui tutti i test almeno una volta
   - Prepara risposte alle domande teoriche
   - Esegui valgrind per verificare memoria

2. **Durante la Difesa:**
   - Mantieni calma
   - Se non sai risposta: "Lasciami controllare il codice"
   - Mostra il codice quando utile
   - Ammetti quando non sai qualcosa
   - Non inventare risposte

3. **Demo:**
   - Compila davanti al correttore
   - Esegui test interattivi
   - Mostra valgrind
   - Testa casi limite

### Per il Correttore

1. **Setup:**
   - Clona repo studente
   - Verifica che compili
   - Prepara terminali multipli

2. **Testing Sistematico:**
   - Segui ordine checklist
   - Annota risultati per ogni test
   - Testa casi limite
   - Prova a "rompere" il programma

3. **Domande:**
   - Inizia con domande base
   - Procedi a domande avanzate
   - Valuta comprensione, non memorizzazione
   - Chiedi di mostrare codice

4. **Valutazione Finale:**
   - Calcola punteggio totale
   - Considera bonus se applicabili
   - Fornisci feedback costruttivo
   - Indica aree di miglioramento

---

## 📝 NOTE FINALI

Questa guida è **completa e esaustiva** per la correzione di Minishell. Copre:

- ✅ Tutti i test pratici obbligatori
- ✅ Tutte le domande teoriche comuni
- ✅ Domande avanzate e casi limite
- ✅ Test di robustezza
- ✅ Valutazione memoria (Valgrind)
- ✅ Checklist finale completa
- ✅ Grading rubric dettagliato

**Tempo Stimato Correzione:** 45-60 minuti

**Good luck! 🚀**
