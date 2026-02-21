# minishell

**minishell** è un progetto del Common Core di 42 che consiste nell’implementare una
**shell minimale**, ispirata a bash, rispettando vincoli rigorosi su parsing, processi,
segnali e gestione della memoria.

L’obiettivo del progetto è comprendere a fondo:
- come funziona una shell
- come vengono gestiti i processi Unix
- come trasformare una stringa di input in comandi eseguibili

---

## Stato attuale del progetto

✅ **Il progetto è COMPLETO e FUNZIONANTE** con:
- Implementazione full della shell minimale
- Tutti i builtin richiesti (echo, cd, pwd, env, export, unset, exit)
- Pipe, redirections, heredoc
- Gestione segnali robusta (Ctrl+C, Ctrl+D, Ctrl+\)
- Valgrind clean (zero memory leaks)
- Exit codes corretti
- Nested minishell support

**Ultima sessione (23 Jan 2026):** 
- Corretti bug Valgrind (invalid reads, segfaults)
- Implementato SIGINT handling robusto in heredoc
- Exit code 2 per errori sintassi
- Refactoring per Norminette compliance (42 header, TOO_MANY_ARGS fix)

---

## Schema logico della shell

La shell è progettata secondo il seguente flusso:

readline()
↓
LEXER
↓
EXPANDER
↓
PARSER
↓
EXECUTOR

---

## Struttura del progetto

```
minishell/
├── Makefile                    # Build system
├── includes/
│   └── minishell.h            # Main header
├── src/
│   ├── main.c                 # Entry point
│   ├── prompt.c               # Readline loop & input processing
│   ├── prompt_utils.c         # Prompt helpers
│   ├── signal.c               # Signal handlers
│   ├── env_utils.c            # Environment utilities
│   ├── debug.c                # Debug utilities
│   ├── lexer/                 # Tokenization
│   │   ├── lexer.c
│   │   ├── lexer_utils.c
│   │   ├── lexer_state.c
│   │   ├── lexer_tokens.c
│   │   └── lexer_helper.c
│   ├── parser/                # Parsing to commands
│   │   ├── parser.c
│   │   ├── parser_utils.c
│   │   ├── parser_redir.c
│   │   └── parser_single_cmd.c
│   ├── expander/              # Variable expansion & quotes
│   │   ├── expander.c
│   │   ├── expander_utils.c
│   │   ├── expander_var.c
│   │   ├── expander_cmds.c
│   │   ├── expander_args.c
│   │   ├── heredoc.c
│   │   ├── heredoc_utils.c
│   │   └── heredoc_signal.c
│   ├── executor/              # Command execution
│   │   ├── executor.c
│   │   ├── executor_utils.c
│   │   ├── executor_exec.c
│   │   ├── executor_redirections.c
│   │   ├── executor_single_exec.c
│   │   ├── executor_pipeline.c
│   │   ├── executor_pipeline_utils.c
│   │   ├── executor_heredoc.c
│   │   └── executor_heredoc_apply.c
│   └── builtin/               # Built-in commands
│       ├── builtin.c
│       ├── builtin_echo.c
│       ├── builtin_cd.c
│       ├── builtin_pwd.c
│       ├── builtin_env.c
│       ├── builtin_export.c
│       ├── builtin_unset.c
│       ├── builtin_exit.c
│       ├── builtin_exit_utils.c
│       ├── export_helpers.c
│       ├── export_helpers_extra.c
│       ├── export_utils.c
│       ├── export_new_var.c
│       └── export_env_dup.c
└── libft/                     # Utility library
    └── *.c, libft.h
```



> La suddivisione in più file è necessaria per rispettare la **norminette**
> (massimo 5 funzioni per file) e per mantenere una separazione chiara delle responsabilità.

---

## Lexer (tokenizzazione)

Il lexer è responsabile di trasformare la stringa letta da `readline()` in una
lista di **token**.

### Funzionalità previste / implementate

- Riconoscimento delle **parole (WORD)**
- Gestione degli **spazi**
- Gestione delle **pipe (`|`)**
- Gestione delle **quote singole e doppie**
- Errore in caso di **quote non chiuse**
- Nessuna espansione o interpretazione (fase successiva)

Esempio:

```bash
echo "ciao mondo" | cat
