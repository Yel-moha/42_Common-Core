# MINISHELL - CHEAT SHEET DIFESA (ITALIANO)

## 🎯 RISPOSTE RAPIDE ALLE DOMANDE COMUNI

### "Quante variabili globali usate?"
**1 variabile: `g_signal`**

**Perché è obbligatorio:**
- Signal handler non può accedere a variabili locali
- Non può ricevere parametri (solo il numero del segnale)
- Non può ritornare valori al chiamante
- Unico modo per comunicare tra signal handler e main loop

**Esempio:**
```
Utente preme Ctrl+C durante readline
→ OS chiama signal handler (sigint_handler)
→ Handler scrive: g_signal = SIGINT
→ Handler mostra nuova riga e ridisegna prompt (rl_redisplay)
→ Readline continua (SA_RESTART)
→ Main loop chiama handle_signal_interrupt()
→ Imposta shell->exit_code = 130
→ Resetta: g_signal = 0
→ echo $? mostrerà 130
```

---

### "Come gestite le quote annidate?"
Usiamo uno **stato interno** che traccia se siamo dentro:
- Single quote: tutto letterale, niente espansione
- Double quote: variabili espanse, ma pipe/redirect no
- Normale: tutto tokenizzato

**Prima di processare una virgoletta, controlliamo lo stato:**
```c
if (word[i] == '\'' && state != STATE_IN_DOUBLE_QUOTE) {
    // Processa solo se non già in double quote
}
```

---

### "Come funzionano le pipe?"
**Processo:**
1. Parser crea lista di comandi (uno per comando)
2. Per ogni comando: fork() + execve()
3. Colleghiamo stdout di cmd1 a stdin di cmd2
4. Padre aspetta tutti i figli
5. Ritorniamo exit code dell'ultimo comando

```
cat file | grep test | wc -l

Figlio1: cat file → pipe1_write
Figlio2: pipe1_read → grep test → pipe2_write  
Figlio3: pipe2_read → wc -l
```

---

### "Come gestite i file descriptor senza loss?"
**Salva, applica, ripristina:**
```c
int saved_stdin = dup(STDIN_FILENO);    // Salva copia
dup2(file_fd, STDIN_FILENO);            // Ridireziona stdin
// ... esegui comando
dup2(saved_stdin, STDIN_FILENO);        // Ripristina
close(saved_stdin);                     // Pulisci
```

---

### "Cosa sono gli heredoc e come li implementate?"
**Cosa:** Ridirezionamento da input multilinea

```bash
cat << EOF
linea1
linea2
EOF
```

**Come:** 
1. Creiamo file temporaneo in `/tmp`
2. Leggiamo righe finché non troviamo il delimitatore
3. Scriviamo righe nel file temporaneo
4. Ridirezzioniamo stdin del comando da quel file

---

### "Come evitate i memory leak?"
**Valgrind:**
```bash
valgrind --leak-check=full --suppressions=minishell.supp ./minishell
```

**Risultato:** 0 bytes definitely lost

**Come:**
- Funzioni dedicate `free_*()` per ogni struttura
- `ft_strdup()` su ogni stringa copiata
- `close()` per ogni fd aperto
- `free()` per ogni malloc

---

### "Qual è la differenza tra echo builtin e /bin/echo?"
Echo deve essere builtin perché:
- Se eseguito in processo figlio, i comandi `-n` non cambierebbero il comportamento del padre
- Le performance sarebbero peggiori
- Bash lo fa così

**Lo stesso vale per cd, export, unset, etc.**

---

### "Come gestite un comando che non esiste?"
**Errore con messaggio chiaro:**
```bash
minishell$ nonexistent
minishell: nonexistent: command not found
minishell$ echo $?
127
```

Cercchiamo il comando nel PATH, se non lo troviamo, mostriamo errore e usciamo con codice 127.

---

### "Cosa succede con `exit 1 2 3`?"
Exit accetta solo 0 o 1 argomento.

**Se ne riceve più di uno:**
```bash
minishell: exit: too many arguments
```

Exit code non cambia (rimane quello precedente).

---

### "Come gestite ctrl-C durante la digitazione?"
**Readline e signal handler collaborano:**
1. Utente digita "echo hello"
2. Preme Ctrl+C
3. Signal handler (sigint_handler): g_signal = SIGINT
4. Signal handler stampa "\n" e chiama rl_redisplay()
5. Readline continua (SA_RESTART flag attivo)
6. Prompt mostrato automaticamente
7. Main loop chiama handle_signal_interrupt()
8. Imposta exit_code = 130 e resetta g_signal = 0
9. Pronto per nuovo input (buffer pulito da rl_replace_line)

---

### "Qual è la massima lunghezza di una riga?"
**Nessun limite** - usiamo getline() che legge fino a EOF/newline.

Bash ha limite di 256KB circa, ma non è richiesto per 42.

---

### "Come espandete le variabili tipo `$?`?"
Durante l'expander, quando vediamo `$?`:
```c
if (current_var == "?") {
    expand_to_string(str, shell->exit_code);
}
```

Inseriamo il codice di uscita dell'ultimo comando al posto di `$?`.

---

### "Cosa gestite per $$ (PID)?"
```c
if (current_var == "$") {
    pid_t pid = getpid();
    expand_to_string(str, pid);
}
```

Inseriamo il nostro PID.

---

### "Perché non usate system()?"
`system()` crea una shell intera che interpreterebbe i comandi. Vogliamo che siano interpretati da **noi**, non da un'altra shell.

Usiamo fork() + execve() per controllare tutto.

---

### "Come gestite PATH?"
Variabile d'ambiente che contiene directories separate da `:`.

**Quando eseguiamo un comando:**
1. Se contiene `/`, usiamo il path assoluto/relativo
2. Altrimenti, cerchiamo in PATH:
   ```c
   for each dir in PATH.split(":"):
       if (file_exists(dir/command)):
           execve(dir/command)
   ```

Se non trovato → comando not found

---

### "Cosa fate se PATH non è settato?"
```bash
minishell$ unset PATH
minishell$ echo
(ecco, echo funziona perché è builtin)
minishell$ ls
ls: command not found
(ls fallisce perché non è builtin e non è in PATH)
```

---

### "Come gestite cd a HOME senza argomenti?"
```c
char *home = getenv("HOME");
if (!home) home = "/";  // Fallback
chdir(home);
```

---

### "Come gestite cd senza permessi?"
```bash
minishell$ cd /root  # (senza permessi)
minishell: cd: /root: Permission denied
```

`chdir()` ritorna -1, mostriamo errore.

---

### "Come gestite variabili che non esistono in espansione?"
Diventiamo stringa vuota:
```bash
minishell$ echo $UNKNOWN
(nulla - stringa vuota)

minishell$ echo "prefix_$UNKNOWN_suffix"  
prefix__suffix
```

---

### "Usate ricorsione nel parser?"
No, è iterativo. Percorriamo la lista di token sequenzialmente e creiamo comandi.

---

### "Qual è la massima profondità di pipe?"
Nessun limite teorico. Ogni pipe crea un nuovo processo figlio, limitato solo dalla capacità del sistema.

---

### "Come gestite `ls | nonexistent`?"
```bash
minishell$ ls | nonexistent
(ls output)
minishell: nonexistent: command not found
minishell$ echo $?
127
```

ls funziona normalmente, nonexistent non viene trovato, ritorna 127.

---

### "Gestite subshell `(ls)`?"
**No** - non è richiesto dal progetto minima. Se l'utente digita `(ls)` sarà un errore di parsing.

---

### "Gestite `let` o altre builtin speciali?"
No, solo: echo, cd, pwd, export, unset, env, exit.

---

## 📊 VALGRIND CHECK

```bash
cd /home/youssef/github/42_Commoncore/minishell

# Esegui minishell
valgrind --leak-check=full --suppressions=minishell.supp ./minishell

# Digita alcuni comandi
echo hello
export TEST=42
ls | grep mini
cat << EOF
test
EOF
exit

# Controlla risultati - dovrebbe dire:
# definitely lost: 0 bytes in 0 blocks
```

---

## ✅ TEST RAPIDI PRIMA DELLA DIFESA

```bash
# Comando semplice
/bin/ls

# Echo con opzione
echo -n hello

# Variabili
export TEST=hello && echo $TEST

# Codice di uscita
/bin/false && echo $?

# Pipe
echo hello | cat

# Redirections
echo test > /tmp/file && cat /tmp/file

# Heredoc
cat << EOF
test
EOF

# Errore handling
cat << nonexistent
```

---

## 🎓 DURANTE LA DIFESA

✅ **Siate calmi** - avete un'ottima implementazione

✅ **Siate chiari** - spiegate mentre parlate, usate esempi

✅ **Se non sapete** - è OK dire "mi dà un momento per pensare"

✅ **Mostrate il codice** - se vi viene fatta una domanda su come funziona qualcosa, potete far vedere il codice

✅ **Siate orgogliosi** - zero memory leak, codice modulare, tutti i test passano!

---

## 📁 FILE IMPORTANTI DA LEGGERE

- `src/lexer/lexer.c` - Come tokenizzate
- `src/parser/parser_utils.c` - Come parse le quote e i comandi
- `src/expander/expander.c` - Come espandete le variabili
- `src/executor/executor.c` - Come eseguite i comandi
- `src/signal.c` - Gestione segnali
- `GUIDA_DIFESA_ITALIANO.md` - Questa guida completa

---

**Buona fortuna! 🍀**
