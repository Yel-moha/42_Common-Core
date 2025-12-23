# minishell

**minishell** è un progetto del Common Core di 42 che consiste nell’implementare una
**shell minimale**, ispirata a bash, rispettando vincoli rigorosi su parsing, processi,
segnali e gestione della memoria.

L’obiettivo del progetto è comprendere a fondo:
- come funziona una shell
- come vengono gestiti i processi Unix
- come trasformare una stringa di input in comandi eseguibili

---

## 📌 Stato attuale del progetto

Al momento il progetto è nelle **fasi iniziali**, con particolare attenzione a:
- struttura del progetto
- loop principale della shell
- gestione dei segnali
- lexer (tokenizzazione dell’input)

Lo sviluppo segue uno schema preciso e incrementale.

---

## 🧠 Schema logico della shell

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


### Stato attuale nello schema

readline() ✅
LEXER 🟡 (in corso)
EXPANDER ❌
PARSER ❌
EXECUTOR ❌


---

## 🗂️ Struttura del progetto

minishell/
├── Makefile
├── includes/
│   └── minishell.h
├── src/
│   ├── main.c
│   ├── prompt.c
│   ├── signal.c
│   ├── lexer.c
│   ├── lexer_utils.c
│   ├── lexer_state.c
│   ├── lexer_tokens.c
│   ├── parser.c
│   ├── parser_utils.c
│   ├── executor.c
│   └── executor_utils.c
└── libft/



> La suddivisione in più file è necessaria per rispettare la **norminette**
> (massimo 5 funzioni per file) e per mantenere una separazione chiara delle responsabilità.

---

## 🔍 Lexer (tokenizzazione)

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
