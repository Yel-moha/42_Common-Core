*This project has been created as part of the 42 curriculum by yel-moha and anacotti *

# minishell

## Description
`minishell` is a simplified UNIX shell written in C as part of the 42 Common Core.

The main goal is to understand how a real shell works by implementing the full command pipeline:
- input reading and prompt handling,
- lexical analysis (tokenization),
- parsing into command structures,
- environment and exit-status expansion,
- execution of built-ins and external commands,
- pipes, redirections, and heredoc,
- signal handling and process management.

The project reproduces a practical subset of `bash` behavior while respecting 42 constraints (allowed functions, norminette, memory safety).

## Instructions
### Prerequisites
- Linux (or a compatible UNIX environment)
- `gcc`
- `make`
- `readline` development library

### Compilation
From the project root:

```bash
make
```

Useful build targets:

```bash
make clean
make fclean
make re
```

### Execution
Run the shell in interactive mode:

```bash
./minishell
```

Run a non-interactive command (example):

```bash
echo 'echo hello | cat' | ./minishell
```

### What is implemented
- Built-ins: `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`
- Pipes: `|`
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Environment expansion: `$VAR`, `$?`
- Quote handling: single and double quotes
- Signal handling (`Ctrl+C`, `Ctrl+\`, `Ctrl+D` behavior)

## Resources
Classic references used to study shell behavior and UNIX process management:
- GNU Bash Manual: https://www.gnu.org/software/bash/manual/
- POSIX Shell Command Language: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- Linux man pages: https://man7.org/linux/man-pages/
- `readline` documentation: https://tiswww.case.edu/php/chet/readline/rltop.html
- Beej’s Guide to Unix IPC (pipes/process fundamentals): https://beej.us/guide/bgipc/

### AI usage disclosure
AI tools were used as a learning and review aid, not as a replacement for implementation work.

Specifically, AI assistance was used for:
- clarifying UNIX concepts (signals, pipes, process lifecycle),
- reviewing edge cases for parsing and syntax validation,
- suggesting debugging/checklist strategies for memory and error handling,
- improving documentation quality and English phrasing.

All core architecture, coding decisions, integration, debugging, and final validation were performed manually in the project codebase.
