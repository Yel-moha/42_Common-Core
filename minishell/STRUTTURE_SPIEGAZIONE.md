# Spiegazione delle Strutture Dati di Minishell

## Indice
1. [Enum vs Struct](#enum-vs-struct)
2. [s_lexer_ctx](#s_lexer_ctx)
3. [s_token](#s_token)
4. [s_redir](#s_redir)
5. [s_cmd](#s_cmd)
6. [s_shell](#s_shell)
7. [s_pipe_state](#s_pipe_state)
8. [s_expand_ctx](#s_expand_ctx)

---

## Enum vs Struct

### **Enum (Enumerazione)**
- Lista di **costanti intere con nomi**
- Usato per **opzioni mutuamente esclusive**
- Occupa lo spazio di un `int` (tipicamente 4 bytes)
- Un enum può avere **solo UN valore alla volta**

**Esempio:**
```c
typedef enum e_token_type {
    T_WORD,          // = 0
    T_PIPE,          // = 1
    T_REDIR_IN,      // = 2
    T_REDIR_OUT,     // = 3
    T_REDIR_APPEND,  // = 4
    T_HEREDOC        // = 5
} t_token_type;
```

### **Struct (Struttura)**
- **Raggruppa variabili di tipi diversi** in un'unica entità
- Ogni campo può contenere dati **simultaneamente**
- Occupa la somma dello spazio di tutti i membri (+ padding)

**Esempio:**
```c
typedef struct s_token {
    t_token_type type;      // enum - il tipo di token
    char *value;            // la stringa del token
    struct s_token *next;   // puntatore al prossimo
} t_token;
```

**In sintesi**: `enum` = scegli UNA opzione tra tante; `struct` = contenitore con PIÙ informazioni diverse.

---

## s_lexer_ctx

**Ruolo**: Contiene il **contesto durante il parsing della linea di comando** (lexing).

```c
typedef struct s_lexer_ctx {
    char    *line;      // La stringa input da analizzare
    int     *i;         // Puntatore all'indice corrente nella scansione
    int     *start;     // Puntatore all'indice di inizio della parola corrente
    t_state *state;     // Puntatore allo stato (normale, apici singoli, doppi, etc)
    t_token **tokens;   // Puntatore al puntatore della lista di token
} t_lexer_ctx;
```

### Variabili spiegate:
- **`line`**: La linea di comando completa da analizzare (es. `"cat file.txt | grep hello"`)
- **`i`**: Indice di scansione carattere per carattere
- **`start`**: Indice di inizio della parola/token corrente
- **`state`**: Traccia se siamo dentro apici singoli, doppi, variabili, ecc.
- **`tokens`**: Puntatore al puntatore per permettere alle funzioni di modificare la testa della lista

### Perché puntatori?
Usano puntatori (invece di valori diretti) per permettere alle funzioni helper di **modificare questi valori e farli persistere** dopo il return.

**Pattern**: `ctx` è abbreviazione di "context" - raggruppa tutti i dati necessari in un'unica struttura invece di passarli singolarmente a ogni funzione.

---

## s_token

**Ruolo**: Rappresenta un **singolo token** generato dal lexer.

```c
typedef struct s_token {
    t_token_type type;      // Tipo di token (WORD, PIPE, REDIR_IN, ecc)
    char        *value;     // La stringa effettiva del token
    int         expand;     // Flag: espandere variabili? (1=sì, 0=no)
    struct s_token *next;   // Puntatore al token successivo (lista concatenata)
} t_token;
```

### Variabili spiegate:
- **`type`**: Categorizza il token (vedi enum `e_token_type`)
  - `T_WORD` = parola normale
  - `T_PIPE` = pipe `|`
  - `T_REDIR_IN` = redirect input `<`
  - `T_REDIR_OUT` = redirect output `>`
  - `T_REDIR_APPEND` = append `>>`
  - `T_HEREDOC` = heredoc `<<`

- **`value`**: La stringa del token
  - Se `type = T_WORD`: il testo della parola (es. "cat", "file.txt")
  - Se `type = T_PIPE`: "|"
  - Se `type = T_REDIR_IN`: "<"

- **`expand`**: Flag booleano (1 = sì espandi, 0 = no)
  - Usato per tracciare se dentro apici singoli (no expand) vs doppi/no-quotes (sì expand)

- **`next`**: Puntatore al token successivo per formare una **lista concatenata**

### Esempio pratico di lexing:
```bash
cat < file.txt | grep "$USER"
```

Diventa:
```
Token 1: {type=T_WORD,     value="cat",     expand=0, next→}
Token 2: {type=T_REDIR_IN, value="<",       expand=0, next→}
Token 3: {type=T_WORD,     value="file.txt",expand=0, next→}
Token 4: {type=T_PIPE,     value="|",       expand=0, next→}
Token 5: {type=T_WORD,     value="grep",    expand=0, next→}
Token 6: {type=T_WORD,     value="$USER",   expand=1, next→NULL}
```

---

## s_redir

**Ruolo**: Rappresenta una **singola redirezione** per un comando.

```c
typedef struct s_redir {
    t_token_type type;      // Tipo di redirezione (IN, OUT, APPEND, HEREDOC)
    char        *target;    // Nome del file di destinazione
    int         heredoc_fd; // File descriptor per heredoc
    struct s_redir *next;   // Puntatore alla prossima redirezione (lista)
} t_redir;
```

### Variabili spiegate:
- **`type`**: Tipo di redirezione
  - `T_REDIR_IN` → `<` (redirect input)
  - `T_REDIR_OUT` → `>` (redirect output)
  - `T_REDIR_APPEND` → `>>` (append)
  - `T_HEREDOC` → `<<` (heredoc)

- **`target`**: Nome del file
  - Es. in `cat < input.txt`, target = `"input.txt"`

- **`heredoc_fd`**: File descriptor usato solo per heredoc
  - Contiene l'FD della pipe dove sono stati scritti i dati dell'heredoc
  - Per altre redirezioni rimane `-1` o non usato

- **`next`**: Puntatore alla **prossima redirezione** (lista concatenata)

### Perché una lista?
Un comando può avere **multiple redirezioni**:
```bash
cat < input.txt > output.txt 2> error.log
```

Ogni redirezione diventa un nodo nella lista:
```
redir1: {type=T_REDIR_IN,  target="input.txt",  next→}
redir2: {type=T_REDIR_OUT, target="output.txt", next→}
redir3: {type=T_REDIR_OUT, target="error.log",  next=NULL}
```

---

## s_cmd

**Ruolo**: Rappresenta un **singolo comando** nella pipeline.

```c
typedef struct s_cmd {
    char    **argv;      // Array NULL-terminated di argomenti
    t_redir *redirs;     // Lista di redirezioni per questo comando
    struct s_cmd *next;  // Puntatore al comando successivo (pipeline)
} t_cmd;
```

### Variabili spiegate:
- **`argv`**: Array di stringhe (come in `main(argc, argv)`)
  - `argv[0]` = nome del comando
  - `argv[1]`, `argv[2]`, ... = argomenti
  - Ultimo elemento = `NULL` (NULL-terminated)
  
  Esempio per `ls -la /home`:
  ```
  argv[0] = "ls"
  argv[1] = "-la"
  argv[2] = "/home"
  argv[3] = NULL
  ```

- **`redirs`**: Puntatore alla testa della lista di redirezioni per questo comando
  - Se nessuna redirezione: `NULL`

- **`next`**: Puntatore al comando successivo nella **pipeline**
  - Se è l'ultimo comando: `NULL`

### Esempio pratico - Pipeline:
```bash
cat file.txt | grep "hello" | wc -l
```

Diventa una lista di 3 comandi:
```
cmd1: {argv=["cat","file.txt",NULL], redirs=NULL, next→}
cmd2: {argv=["grep","hello",NULL],   redirs=NULL, next→}
cmd3: {argv=["wc","-l",NULL],        redirs=NULL, next=NULL}
```

Ogni `|` crea un nuovo nodo `s_cmd`.

---

## s_shell

**Ruolo**: Contiene il **contesto globale della shell** durante l'esecuzione.

```c
typedef struct s_shell {
    char    **envp_copy;   // Copia modificabile delle variabili di ambiente
    int     exit_code;     // Codice di uscita dell'ultimo comando
    int     should_exit;   // Flag: la shell deve terminare? (1=sì, 0=no)
} t_shell;
```

### Variabili spiegate:
- **`envp_copy`**: Copia modificabile dell'ambiente (`envp`)
  - Array di stringhe nel formato `"NOME=valore"`
  - Copiata da `main()` all'inizio per non modificare l'ambiente padre
  - Aggiornata da `export`, `unset`, `cd` (PWD)
  - Passata ai processi figli tramite `execve()`

- **`exit_code`**: Codice di uscita dell'ultimo comando
  - Usato dalla variabile speciale `$?`
  - Ritornato al terminale quando la shell termina
  - Aggiornato dopo ogni comando

- **`should_exit`**: Flag booleano per terminare
  - `0` = continua il loop del prompt
  - `1` = esci dal prompt loop
  - Impostato da `builtin_exit()` o errori critici

### Ruolo centrale:
`s_shell` è il **contesto globale** - contiene tutte le informazioni di stato necessarie. Viene passato a:
- Lexer/Parser/Executor
- Builtin commands
- Expander (per accedere alle variabili di ambiente)

**Esempio di utilizzo:**
```c
t_shell shell;
shell.envp_copy = copy_envp(envp);
shell.exit_code = 0;
shell.should_exit = 0;

while (!shell.should_exit) {
    // prompt loop
}
```

---

## s_pipe_state

**Ruolo**: Mantiene lo stato della **pipeline** durante l'esecuzione di comandi concatenati.

```c
typedef struct s_pipe_state {
    int *fd;        // Puntatore ad array [read_end, write_end] della pipe corrente
    int prev_fd;    // File descriptor di lettura della pipe precedente
} t_pipe_state;
```

### Variabili spiegate:
- **`fd`**: Puntatore ad array di 2 file descriptor creato da `pipe()`
  - `fd[0]` = estremità di **lettura** della pipe
  - `fd[1]` = estremità di **scrittura** della pipe
  - Rappresenta la pipe **corrente** tra due comandi consecutivi

- **`prev_fd`**: File descriptor dell'estremità di lettura della pipe **precedente**
  - Usato per redirigere lo `stdin` del comando corrente
  - Inizializzato a `-1` per il primo comando (nessun input da pipe)

### Come funziona in una pipeline:

```bash
cmd1 | cmd2 | cmd3
```

**Durante l'esecuzione:**

1. **cmd1**:
   - `prev_fd = -1` (nessuna pipe precedente)
   - Crea pipe → `fd[0]`, `fd[1]`
   - Output → `fd[1]` (stderr → stdout)

2. **cmd2**:
   - `prev_fd = fd[0]` della pipe precedente (da cmd1)
   - Stdin ← `prev_fd`
   - Crea nuova pipe → `fd[0]`, `fd[1]`
   - Output → `fd[1]` (verso cmd3)

3. **cmd3**:
   - `prev_fd = fd[0]` della pipe precedente (da cmd2)
   - Stdin ← `prev_fd`
   - Nessuna nuova pipe (ultimo comando)
   - Output → stdout normale

**In sintesi**: `s_pipe_state` mantiene traccia della "catena" di pipe per collegare stdin/stdout tra comandi consecutivi.

---

## s_expand_ctx

**Ruolo**: Contiene il **contesto durante l'espansione di variabili e caratteri speciali** in una parola.

```c
typedef struct s_expand_ctx {
    char    *res;       // Stringa risultato (la parola espansa)
    char    *word;      // La parola originale da espandere
    int     *i;         // Puntatore all'indice di scansione nella parola
    t_state *state;     // Puntatore allo stato (normale, apici singoli, doppi, etc)
} t_expand_ctx;
```

### Variabili spiegate:
- **`res`**: Stringa **accumulatrice** che contiene il risultato dell'espansione
  - Inizialmente stringa vuota `""`
  - Viene riempita carattere per carattere durante l'espansione
  - Contiene variabili di ambiente espanse, tilde espansa, ecc.

- **`word`**: La parola **originale** che deve essere espansa
  - Es. `"$HOME/Desktop"` o `"echo~"` o `"file*.txt"`
  - Rimane invariata durante il processo

- **`i`**: Puntatore all'indice di scansione nella parola
  - Traccia la posizione corrente durante l'iterazione
  - Puntatore perché le funzioni helper devono modificarlo e far persistere il valore

- **`state`**: Puntatore allo stato del parsing
  - Traccia se siamo dentro apici singoli (no expand), doppi (expand), ecc.
  - Determina come processare i caratteri speciali

### Esempio pratico di espansione:

```bash
echo "$HOME/test" | grep 'pattern'
```

**Token "$HOME/test"** (expand=1 → deve expandere):

```
Input:  "$HOME/test"
        ↓
Scansione carattere per carattere:
  i=0: '$'  → riconosce variable expansion
       → legge "HOME"
       → cerca in envp_copy
       → aggiunge "/home/youssef" a res
  i=5: '/'  → carattere normale
       → aggiunge "/" a res
  i=6-9: 'test' → caratteri normali
         → aggiunge "test" a res
        ↓
Output: "/home/youssef/test"
```

### Flusso completo:

```c
t_expand_ctx ctx;
ctx.res = ft_strdup("");         // Inizializza risultato vuoto
ctx.word = word;                 // Parola da espandere
ctx.i = &(int){0};               // Indice = 0
ctx.state = &state;              // Stato = normale

while (word[*(ctx.i)]) {
    process_word_char(&ctx, shell);  // Processa un carattere
    // ctx.i viene incrementato dalla funzione
}

return (ctx.res);                // Ritorna la parola espansa
```

---

## Schema Completo del Flusso

```
INPUT: "cat file.txt | grep hello > out.txt"
       ↓
LEXER (usando s_lexer_ctx)
       ↓
Lista di s_token
       ↓
PARSER
       ↓
Lista di s_cmd (con s_redir associate)
       ↓
EXPANDER (usando s_expand_ctx)
       ↓
EXECUTOR (usando s_shell e s_pipe_state)
       ↓
OUTPUT
```

---

## Riassunto Rapido

| Struttura | Quando | Cosa fa |
|-----------|--------|---------|
| `s_lexer_ctx` | **Lexing** | Contiene dati per scansionare la linea di comando |
| `s_token` | **Lexer** | Rappresenta un singolo token (WORD, PIPE, REDIR, ecc) |
| `s_redir` | **Parser** | Rappresenta una singola redirezione (`<`, `>`, `>>`, `<<`) |
| `s_cmd` | **Parser** | Rappresenta un comando con argomenti e redirezioni |
| `s_shell` | **Runtime** | Contiene lo stato globale della shell |
| `s_pipe_state` | **Executor** | Mantiene traccia delle pipe tra comandi |
| `s_expand_ctx` | **Expander** | Contiene il contesto durante l'espansione di variabili |
