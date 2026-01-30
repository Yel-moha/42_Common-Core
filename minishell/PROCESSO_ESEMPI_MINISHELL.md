# Processo completo e 10 esempi di esecuzione

Questo documento descrive **passo‑passo** tutto il flusso di esecuzione, seguendo le funzioni coinvolte e spiegando ogni singola riga/istruzione rilevante. Alla fine trovi **10 esempi diversi** (con pipe e heredoc) e l’ordine preciso delle funzioni percorse.

> Nota: i nomi delle funzioni sono evidenziati con `backticks` e la spiegazione è costruita sulle funzioni presenti nel progetto.

---

## 1) Flusso generale (catena di chiamate)

**Avvio programma → prompt → lexer → parser → expander → executor → builtins/execve**

1. `main()` inizializza la shell, prepara la copia dell’ambiente, imposta i segnali, avvia il loop del prompt.
2. `prompt_loop()` gestisce input, storia e terminazione.
3. `execute_parsing_and_execution()` coordina `lexer()` → `parse_tokens()` → `expand_cmds()` → `execute_cmds()`.
4. `execute_cmds()` sceglie tra `execute_single_cmd()` o `execute_pipeline()`.
5. L’esecuzione avviene tramite builtins o `execve` con gestione redirections, heredoc e segnali.

---

## 2) Spiegazione riga‑per‑riga delle funzioni (senza saltare righe)

### 2.1 Avvio e prompt

**`main()`**
- Dichiara `t_shell shell` per contenere ambiente, exit code e flag di uscita.
- Ignora `ac` e `av` perché non usa argomenti da riga di comando.
- Se `envp` è nullo, ritorna `1` (errore).
- `shell.envp_copy = copy_envp(envp)` crea una copia modificabile dell’ambiente.
- Se la copia fallisce, ritorna `1`.
- Inizializza `shell.exit_code = 0` e `shell.should_exit = 0`.
- `init_signals()` configura la gestione di `SIGINT` e ignora `SIGQUIT`.
- `prompt_loop(&shell)` entra nel ciclo principale.
- `free_envp(shell.envp_copy)` libera l’ambiente quando il loop termina.
- Ritorna `shell.exit_code`.

**`copy_envp()`**
- Se `envp` è nullo, ritorna `NULL`.
- `count_envp()` conta le stringhe fino al terminatore `NULL`.
- `alloc_and_copy_envp()` alloca e duplica ogni entry con `ft_strdup`.
- In caso di fallimento di una `ft_strdup`, libera le entry già allocate e ritorna `NULL`.

**`init_signals()`**
- Prepara una `sigaction` con `sigint_handler`.
- `sigemptyset` azzera la mask.
- `sa_flags = SA_RESTART` fa riprendere le syscall interrotte.
- `sigaction(SIGINT, ...)` installa il handler.
- `signal(SIGQUIT, SIG_IGN)` ignora `SIGQUIT`.

**`sigint_handler()`**
- Imposta `g_signal = SIGINT`.
- Scrive un newline.
- `rl_on_new_line()` prepara readline per una nuova riga.
- `rl_replace_line("", 0)` svuota la linea corrente.
- `rl_redisplay()` ridisegna il prompt.

**`prompt_loop()`**
- Ciclo infinito `while (1)`.
- `line = readline("minishell$ ")` legge input.
- `handle_signal_interrupt(shell, &line)` gestisce `SIGINT` e possibili linee vuote.
- Se `line` è `NULL`, stampa `exit` e chiama `cleanup_and_exit()`.
- Se la linea è vuota o solo spazi/tab (`only_spaces()`), la libera e continua.
- `add_history(line)` inserisce la linea in history.
- `process_input(line, shell)` avvia parsing/esecuzione.
- `free(line)` libera la stringa dell’input.

**`handle_signal_interrupt()` (versione del prompt)**
- Se `g_signal == SIGINT`, imposta `shell->exit_code = 130`, azzera `g_signal`.
- Se la linea è `NULL`, ritorna `1` per far ripartire il loop.
- Se la linea è vuota, libera e ritorna `1`.
- Altrimenti ritorna `0`.

**`only_spaces()`**
- Scorre la stringa; se trova un carattere diverso da spazio o tab, ritorna `0`.
- Se termina senza trovarli, ritorna `1`.

**`cleanup_and_exit()`**
- `free_envp(shell->envp_copy)` libera l’ambiente.
- `rl_clear_history()` libera la history di readline.
- `exit(shell->exit_code)` termina il processo.

**`process_input()`**
- Chiama `execute_parsing_and_execution()`.
- Se `shell->should_exit` è impostato, chiama `cleanup_and_exit()`.

**`execute_parsing_and_execution()`**
- `lexer(line)` tokenizza.
- Se `lexer` ritorna `NULL`, stampa errore di quote non chiuse, setta `exit_code=2` e ritorna.
- `parse_tokens(tokens)` costruisce la lista di `t_cmd`.
- Se parsing fallisce, setta `exit_code=2`, libera tokens e ritorna.
- `expand_cmds(cmd, shell)` espande variabili e quote.
- `free_tokens(tokens)` rilascia i token.
- `execute_cmds(cmd, shell)` esegue.
- `free_cmds(cmd)` libera la lista comandi.

---

### 2.2 Lexer (tokenizzazione)

**`lexer()`**
- Inizializza `tokens = NULL`, `i = 0`, `start = -1`, `state = STATE_NORMAL`.
- Prepara un contesto `t_lexer_ctx` con puntatori a questi valori.
- Cicla su ogni carattere della linea e chiama `process_token_char()`.
- Se il `state` non è `STATE_NORMAL`, libera tokens e ritorna `NULL` (quote non chiuse).
- `handle_word_end()` aggiunge l’ultimo token parola se necessario.
- Ritorna la lista dei token.

**`process_token_char()`**
- `handle_char()` aggiorna lo stato quote.
- Se il carattere è spazio e si è in `STATE_NORMAL`, chiude la parola con `handle_word_end()`.
- Se il carattere è `|` e `STATE_NORMAL`, chiude la parola, aggiunge un token `T_PIPE`, incrementa `i` e ritorna.
- Se è redirection (`<` o `>`) in `STATE_NORMAL`, chiude la parola e chiama `handle_redir()`.
- Se `start == -1`, imposta l’inizio della parola.
- Incrementa `i`.

**`handle_char()`**
- Se `line` o `state` sono null, ritorna.
- Chiama `update_state()` con il carattere corrente.

**`update_state()`**
- Se trova `'` o `"` alterna tra stato normale e stato dentro quote.
- Altrimenti ritorna lo stato invariato.

**`handle_redir()`**
- Controlla se c’è redirection doppia (`<<` o `>>`).
- Se doppia, aggiunge `T_HEREDOC` o `T_REDIR_APPEND` e incrementa `i` di 2.
- Se singola, aggiunge `T_REDIR_IN` o `T_REDIR_OUT` e incrementa `i` di 1.

**`handle_word_end()`**
- Se `start != -1`, chiama `add_word()` per creare `T_WORD`.
- Resetta `start = -1`.

**`add_word()`**
- Se `end <= start`, non fa nulla.
- `ft_substr` estrae la parola.
- Salta eventuali spazi iniziali.
- Se la parola è vuota, libera e ritorna.
- Aggiunge `T_WORD` con `add_token()`.

**`add_token()`**
- Se la lista è vuota, imposta la testa.
- Altrimenti scorre e appende in coda.

**`new_token()`**
- Alloca un `t_token`, imposta `type`, `value`, `next=NULL`.

**`free_tokens()`**
- Scorre la lista, libera `value` e il nodo.

**`is_space()` / `is_redir()` / `is_operator()` / `is_double_redir()`**
- Funzioni di utilità per riconoscere spazi e operatori.

---

### 2.3 Parser

**`parse_tokens()`**
- Se `validate_pipes()` fallisce, ritorna `NULL`.
- Scorre la lista dei token e chiama `parse_single_cmd()` per ogni segmento.
- Collega i comandi in lista con `next`.
- Se incontra `T_PIPE`, avanza oltre il pipe.

**`validate_pipes()`**
- Se la lista è vuota, ritorna `0`.
- Se il primo token è `T_PIPE`, stampa errore e ritorna `-1`.
- Scorre i token: se trova `T_PIPE` seguito da `NULL` o da un altro `T_PIPE`, stampa errore e ritorna `-1`.
- Altrimenti ritorna `0`.

**`parse_single_cmd()`**
- `new_cmd()` alloca un comando con `argv=NULL`, `redirs=NULL`, `next=NULL`.
- `count_argv_tokens()` conta quante parole non sono redirection.
- Alloca `argv` di dimensione `argc + 1`.
- `fill_argv_only()` copia solo i `T_WORD` in `argv`.
- `fill_redirs_only()` crea la lista redirections.
- Se errore redirection, libera e ritorna `NULL`.
- Avanza i token fino a `T_PIPE`.

**`count_argv_tokens()`**
- Scorre token fino a `T_PIPE`.
- Conta `T_WORD`.
- Se vede una redirection, salta il target.

**`fill_argv_only()`**
- Se `T_WORD`, duplica il valore.
- Se redirection, salta il target.
- Termina `argv` con `NULL` e ritorna `argc`.

**`fill_redirs_only()`**
- Se redirection senza target `T_WORD`, stampa errore e libera `argv` parziale.
- Altrimenti aggiunge redirection con `process_redir_token()`.

**`process_redir_token()`**
- Crea una redirection `t_redir` e la aggiunge alla lista.

**`new_redir()`**
- Alloca `t_redir`, duplica `target`, imposta `heredoc_fd = -1`.

**`add_redir()`**
- Aggiunge la redirection in coda.

**`free_cmds()`**
- Scorre la lista comandi: libera `argv` con `free_argv()`, redirections con `free_redirs()` e il nodo.

**`free_redirs()`**
- Scorre le redirections, chiude eventuale `heredoc_fd` valido, libera `target` e nodo.

---

### 2.4 Expander (variabili e quote)

**`expand_cmds()`**
- Per ogni comando:
  - `expand_argv()` espande ogni argomento.
  - `handle_empty_argv()` elimina eventuale `argv[0]` vuoto.
  - `expand_redirs()` espande i target delle redirections.
  - `split_argv_if_needed()` divide il primo argomento se contiene spazi.

**`expand_argv()`**
- Cicla sugli argomenti e sostituisce ogni stringa con `expand_word()`.

**`expand_word()`**
- Inizializza `state = STATE_NORMAL`.
- Crea `ctx.res` come stringa vuota.
- Scorre ogni carattere e chiama `process_word_char()`.
- Libera la parola originale e ritorna la stringa espansa.

**`process_word_char()`**
- Gestisce quote singole/doppie aggiornando `state`.
- Se trova `$` fuori dalle quote singole, chiama `handle_expansion()`.
- Altrimenti aggiunge carattere con `append_char()`.

**`handle_expansion()`**
- Se `$?` o nome variabile valido, usa `expand_variable()`.
- Altrimenti inserisce il carattere `$`.

**`expand_variable()`**
- Salta `$`.
- Se `?`, usa `expand_exit_code()`.
- Se digit, ignora (nessuna espansione).
- Altrimenti usa `expand_env_var()`.

**`expand_env_var()`**
- Estrae il nome variabile con `extract_var_name()`.
- Cerca il valore con `get_env_value()`.
- Se esiste, concatena al risultato.

**`expand_exit_code()`**
- Converte `shell->exit_code` in stringa con `ft_itoa` e la concatena.

**`append_char()`**
- Crea una stringa temporanea e concatena un carattere.

**`handle_empty_argv()`**
- Se `argv[0]` diventa vuoto, lo rimuove e compatta `argv`.

**`expand_redirs()`**
- Per ogni redirection, espande il `target` con `expand_word()`.

**`split_argv_if_needed()`**
- Se `argv[0]` contiene spazi, usa `ft_split` e aggiunge i token extra con `add_arg_to_cmd()`.

**`add_arg_to_cmd()`**
- Conta argomenti con `count_argv()`.
- Crea un nuovo `argv` con uno slot in più e inserisce il nuovo argomento.

---

### 2.5 Heredoc (lettura e gestione)

**`process_heredocs()`**
- Scorre i comandi e le redirections.
- Per ogni `T_HEREDOC`, chiama `setup_heredoc_redir()`.

**`setup_heredoc_redir()`**
- Crea una pipe.
- Salva `STDIN`.
- `strip_quotes()` rimuove eventuali quote dal delimitatore.
- `read_heredoc()` legge fino al delimitatore e scrive nella pipe.
- Salva il lato lettura in `redir->heredoc_fd`.
- Ripristina `STDIN`.

**`read_heredoc()`**
- Installa `heredoc_sigint` come handler temporaneo.
- `g_signal = 0`.
- Decide se espandere con `heredoc_should_expand()`.
- Loop: `read_heredoc_line()` → `handle_heredoc_line()`.
- Ripristina il signal handler originale.

**`read_heredoc_line()`**
- Stampa il prompt `> `.
- Legge caratteri con `read_char_to_line()` finché trova newline o EOF.

**`read_char_to_line()`**
- `read()` un carattere.
- Se newline, segnala fine linea.
- Se EOF e linea vuota, segnala chiusura.
- Se EOF con contenuto, segnala fine.
- Se `EINTR`, segnala errore.

**`handle_heredoc_line()`**
- Se `g_signal == SIGINT`, imposta `exit_code=130` e termina.
- Se la linea è `NULL` o uguale al delimitatore, termina.
- Altrimenti scrive la linea nel fd, espandendo se richiesto.

**`process_heredoc_line()`**
- Se `expand` è vero, usa `expand_word()`.
- Scrive la linea e un newline nel fd.

**`heredoc_should_expand()`**
- Se il delimitatore contiene quote, ritorna `0` (no espansione).
- Altrimenti ritorna `1`.

**`strip_quotes()`**
- Costruisce una stringa senza quote singole o doppie.

**`close_heredoc_fds()`**
- Scorre comandi e chiude ogni `heredoc_fd` valido.

**`close_all_heredoc_fds_except_current()`**
- Chiude gli heredoc dei comandi diversi da quello corrente (usato nelle pipeline).

---

### 2.6 Executor (esecuzione comandi)

**`execute_cmds()`**
- Se non ci sono comandi, ritorna.
- Se c’è più di un comando, chiama `execute_pipeline()`.
- Altrimenti `execute_single_cmd()`.

**`execute_single_cmd()`**
- Chiama `prepare_single_cmd()`.
- Se fallisce, chiude heredoc e ritorna.
- Se `argv` vuoto, imposta `exit_code=0`.
- Altrimenti `handle_builtin_or_exec()`.
- Ripristina i fd originali e chiude heredoc.

**`prepare_single_cmd()`**
- Se `g_signal == SIGINT`, imposta exit e ritorna errore.
- `process_heredocs()` crea i contenuti heredoc.
- Se interrotto, imposta `exit_code=130` e ritorna errore.
- Salva `STDIN` e `STDOUT` con `dup`.
- `apply_redirections()` applica redirections.
- Se errore, ripristina fd e ritorna errore.

**`apply_redirections()`**
- Per ogni redirection:
  - Se file redir, chiama `apply_file_redir()`.
  - Se heredoc, duplica `heredoc_fd` su `STDIN`.

**`apply_file_redir()`**
- Apre file in modalità corretta (input, output, append).
- Se apertura fallisce, stampa errore e ritorna `-1`.
- Duplica fd su `STDIN` o `STDOUT`.
- Chiude il fd.

**`handle_builtin_or_exec()`**
- Se builtin, esegue `run_builtin()` senza fork.
- Altrimenti `fork()`.
- Nel figlio: chiude i fd salvati e chiama `execve_or_die()`.
- Nel padre: `waitpid()` e aggiorna `exit_code` con `update_exit_from_status()`.

**`execve_or_die()`**
- Trova il path con `find_command_path()`.
- Se errore, stampa messaggio e termina il figlio.
- Ripristina segnali con `reset_signals_in_child()`.
- Chiama `execve()`.
- Se fallisce, `perror` e termina.

**`execute_pipeline()`**
- `process_all_heredocs()` pre‑carica gli heredoc per tutta la pipeline.
- Se `SIGINT`, chiude heredoc e ritorna.
- Itera su tutti i comandi:
  - Se c’è un comando successivo, crea una pipe.
  - `spawn_pipeline_child()` avvia il figlio.
  - `close_parent_pipes()` gestisce i fd nel parent.
- Chiude gli heredoc e attende tutti i figli con `wait_all_and_set_exit()`.

**`spawn_pipeline_child()`**
- `fork()` e nel figlio chiama `execute_pipeline_child()`.

**`execute_pipeline_child()`**
- `setup_child_pipes()` duplica fd corretti per stdin/stdout.
- Chiude heredoc degli altri comandi.
- Applica redirections con `apply_redirections()`.
- Esegue con `execve_or_builtin()`.
- Se torna, termina con `cleanup_and_exit_child()`.

**`execve_or_builtin()`**
- Se builtin, esegue e chiude il processo figlio.
- Altrimenti trova path, controlla errori con `exec_error_status()`.
- `execve()` per eseguire il binario.

**`find_command_path()`**
- Se il comando contiene `/`, duplica e ritorna.
- Se `PATH` non esiste, ritorna `NULL`.
- Altrimenti split di `PATH` e ricerca un path eseguibile.

**`exec_error_status()`**
- Gestisce errori: comando non trovato, path non esistente, directory, permessi.
- Ritorna il codice di errore per l’exec.

**`update_exit_from_status()` / `handle_child_exit_signal()`**
- Traducono lo status di `waitpid` in `exit_code`.

**`cleanup_and_exit_child()`**
- Libera comandi e ambiente, pulisce history, chiude processo con `exit()`.

---

### 2.7 Builtins

**`is_builtin()`**
- Confronta il comando con tutti i nomi builtin (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`).

**`run_builtin()`**
- Dispatch verso la builtin corretta.

**`builtin_pwd()`**
- `getcwd()` legge la directory corrente e la stampa.

**`builtin_echo()`**
- Riconosce `-n` ripetuti.
- Stampa gli argomenti separati da spazi e, se richiesto, senza newline.

**`builtin_cd()`**
- Se troppi argomenti, errore.
- Se nessun argomento, usa `HOME`.
- Chiama `chdir()` e aggiorna `PWD`/`OLDPWD`.

**`builtin_env()`**
- Stampa tutte le variabili che contengono `=`.

**`builtin_export()`**
- Se nessun argomento, stampa l’ambiente ordinato.
- Altrimenti esporta variabili.

**`export_var()`**
- Valida l’identificatore.
- Se `KEY=VALUE`, sostituisce o aggiunge.
- Se solo `KEY`, crea entry vuota.

**`builtin_unset()`**
- Rimuove le variabili valide dall’ambiente.

**`builtin_exit()`**
- Stampa `exit`, valida argomento numerico, imposta `should_exit`.

---

## 3) Esempi di esecuzione (10 casi diversi)

Ogni esempio segue **tutta la catena**: prompt → lexer → parser → expander → executor → builtin/exec. I dettagli di ogni funzione sono nella sezione 2.

### Esempio 1 — `pwd`
1. `prompt_loop()` legge la linea.
2. `lexer()` produce un solo `T_WORD` (`pwd`).
3. `parse_tokens()` crea un `t_cmd` con `argv = ["pwd", NULL]`.
4. `expand_cmds()` non modifica nulla.
5. `execute_cmds()` sceglie `execute_single_cmd()`.
6. `handle_builtin_or_exec()` riconosce builtin e chiama `builtin_pwd()`.
7. `builtin_pwd()` usa `getcwd()` e stampa il percorso.

### Esempio 2 — `echo hello`
1. Tokenizzazione: `T_WORD echo`, `T_WORD hello`.
2. Parser: `argv = ["echo", "hello", NULL]`.
3. Expander: nessuna variabile, nulla cambia.
4. Executor: `execute_single_cmd()` → `run_builtin()` → `builtin_echo()`.
5. `builtin_echo()` stampa `hello` con newline.

### Esempio 3 — `echo -n a b`
1. Tokenizzazione: `echo`, `-n`, `a`, `b`.
2. Parser: `argv = ["echo", "-n", "a", "b", NULL]`.
3. Executor: builtin `echo`.
4. `builtin_echo()` rileva `-n` e non stampa newline.

### Esempio 4 — `export MYVAR=42`
1. Tokenizzazione: `export`, `MYVAR=42`.
2. Parser: `argv = ["export", "MYVAR=42", NULL]`.
3. Executor: builtin `export`.
4. `export_var()` valida `MYVAR` e inserisce/aggiorna la variabile.

### Esempio 5 — `echo $MYVAR`
1. Tokenizzazione: `echo`, `$MYVAR`.
2. Expander: `expand_word()` sostituisce `$MYVAR` con il valore nell’ambiente.
3. Executor: builtin `echo` stampa il valore espanso.

### Esempio 6 — `unset MYVAR`
1. Tokenizzazione: `unset`, `MYVAR`.
2. Executor: builtin `unset`.
3. `builtin_unset()` valida il nome e rimuove la variabile con `env_remove_at_index()`.

### Esempio 7 — `cd ..`
1. Tokenizzazione: `cd`, `..`.
2. Executor: builtin `cd`.
3. `builtin_cd()` chiama `chdir("..")` e aggiorna `PWD/OLDPWD`.

### Esempio 8 — `ls -l | grep minishell`
1. Tokenizzazione: `ls`, `-l`, `|`, `grep`, `minishell`.
2. Parser: crea due `t_cmd` concatenati con `next`.
3. Expander: nessuna sostituzione.
4. Executor: `execute_pipeline()`.
5. `spawn_pipeline_child()` crea due processi collegati via pipe.
6. Ogni figlio esegue `execve_or_builtin()` con `execve`.
7. `wait_all_and_set_exit()` aggiorna l’`exit_code` con lo status dell’ultimo comando.

### Esempio 9 — `cat < infile | wc -l > out.txt`
1. Tokenizzazione: `cat`, `<`, `infile`, `|`, `wc`, `-l`, `>`, `out.txt`.
2. Parser: due comandi; redirections associate al comando corretto.
3. Expander: nessuna sostituzione.
4. Executor: pipeline con `apply_redirections()`:
   - Nel primo figlio: `apply_file_redir()` apre `infile` e lo duplica su `STDIN`.
   - Nel secondo figlio: `apply_file_redir()` apre `out.txt` e lo duplica su `STDOUT`.
5. `execve()` esegue `cat` e `wc`.

### Esempio 10 — `cat << EOF | grep foo`
1. Tokenizzazione: `cat`, `<<`, `EOF`, `|`, `grep`, `foo`.
2. Parser: `T_HEREDOC` viene salvato nella redirection del primo comando.
3. `process_all_heredocs()` legge l’input fino a `EOF` e salva su pipe interna.
4. Se il delimitatore fosse quotato (`<< 'EOF'`), `heredoc_should_expand()` disabilita l’espansione.
5. `execute_pipeline()` collega la pipe heredoc al `STDIN` del primo comando e la pipe tra comandi.
6. `grep` filtra le righe contenenti `foo`.

---

## 4) Checklist finale (copertura completa)

- Prompt, segnali e history: coperti.
- Lexer, parser e validazione pipe: coperti.
- Expander, variabili e quote: coperti.
- Redirections e heredoc: coperti.
- Executor singolo e pipeline: coperti.
- Builtins principali: coperti.
- 10 esempi diversi, con pipe e heredoc inclusi: completati.
