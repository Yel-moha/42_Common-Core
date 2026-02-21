# Minishell - Development Guide

A complete guide for collaborators to understand and work on the minishell project.

**Last Updated:** February 21, 2026  
**Status:** Functionally complete with robust signal handling and heredoc support.

## Table of Contents
1. [Project Overview](#project-overview)
2. [Project Architecture](#project-architecture)
3. [Code Structure](#code-structure)
4. [Data Structures](#data-structures)
5. [Module Reference](#module-reference)
6. [Coding Standards](#coding-standards)
7. [Building & Testing](#building--testing)
8. [Final Session Summary](#final-session-summary)
9. [Common Modifications](#common-modifications)

---

## Project Overview

**Minishell** is a simplified UNIX shell implementation written in C that mimics the behavior of bash. It includes:
- Command parsing and execution
- Built-in commands (echo, cd, pwd, env, export, unset, exit)
- Redirections (>, >>, <, <<)
- Pipes (|)
- Variable expansion ($VAR, $?)
- Quote handling (single and double quotes)
- Signal handling

---

## Project Architecture

The project follows a modular pipeline architecture:

```
USER INPUT
    ↓
LEXER (tokenization)
    ↓
PARSER (command structure)
    ↓
EXPANDER (variable/quote expansion)
    ↓
EXECUTOR (execution + redirections)
    ↓
BUILTIN/EXTERNAL (command execution)
```

Each module is independent and communicates through defined data structures.

---

## Code Structure

```
minishell/
├── Makefile              # Build configuration
├── includes/
│   └── minishell.h       # Main header with all prototypes and structs
├── libft/                # Custom C library
│   ├── libft.h
│   └── *.c               # String, memory, list utilities
├── src/
│   ├── main.c            # Entry point
│   ├── prompt.c          # Main loop & readline
│   ├── prompt_utils.c    # Prompt helper functions
│   ├── signal.c          # Signal handlers (SIGINT, SIGQUIT)
│   ├── env_utils.c       # Environment variable utilities
│   ├── debug.c           # Debug printing functions
│   ├── lexer/            # Tokenization module
│   ├── parser/           # Parsing module (parser.c, parser_utils.c, parser_redir.c, parser_single_cmd.c)
│   ├── expander/         # Expansion module (expander.c, expander_utils.c, expander_var.c, expander_cmds.c, expander_args.c, heredoc*.c)
│   ├── executor/         # Execution module (executor.c + pipeline/exec/redir/heredoc splits)
│   └── builtin/          # Built-in commands (+ export/exit helper splits)
```

---

## Data Structures

### Token Structure (`t_token`)
```c
typedef struct s_token
{
    t_token_type    type;       // T_WORD, T_PIPE, T_REDIR_*, T_HEREDOC
    char           *value;      // Token content
    struct s_token *next;       // Linked list
    int             expand;     // Whether to expand this token
}   t_token;
```

### Redirection Structure (`t_redir`)
```c
typedef struct s_redir
{
    t_token_type    type;       // T_REDIR_IN, T_REDIR_OUT, T_REDIR_APPEND, T_HEREDOC
    char           *target;     // File name or heredoc delimiter
    int             heredoc_fd; // File descriptor for heredoc content
    struct s_redir *next;       // Linked list
}   t_redir;
```

### Command Structure (`t_cmd`)
```c
typedef struct s_cmd
{
    char          **argv;       // Command arguments (NULL-terminated)
    t_redir       *redirs;      // Redirections linked list
    struct s_cmd  *next;        // For pipe chains
}   t_cmd;
```

### Shell Structure (`t_shell`)
```c
typedef struct s_shell
{
    char **envp_copy;   // Modifiable copy of environment
    int   exit_code;    // Last command exit status
}   t_shell;
```

### State Enum (`t_state`)
```c
typedef enum e_state
{
    STATE_NORMAL,              // Outside quotes
    STATE_IN_SINGLE_QUOTE,     // Inside single quotes
    STATE_IN_DOUBLE_QUOTE,     // Inside double quotes
    STATE_IN_VAR_EXPANSION     // During variable expansion
}   t_state;
```

---

## Module Reference

### 1. LEXER Module (`src/lexer/`)
**Purpose:** Converts input string into tokens.

| File | Function | Purpose |
|------|----------|---------|
| `lexer.c` | `t_token *lexer(char *line)` | Main lexer - tokenizes input |
| `lexer_state.c` | `t_state update_state(char c, t_state state)` | Updates quote state based on character |
| `lexer_state.c` | `void handle_char(char *line, int i, t_state *state)` | Updates state for current character |
| `lexer_tokens.c` | `t_token *new_token(t_token_type type, char *value)` | Creates new token |
| `lexer_tokens.c` | `void add_token(t_token **head, t_token *new)` | Adds token to list |
| `lexer_tokens.c` | `void add_word(t_token **tokens, char *line, int start, int end)` | Extracts word from line |
| `lexer_helper.c` | `void handle_redir(t_token **tokens, char *line, int *i)` | Handles >, >>, < redirections |
| `lexer_helper.c` | `int is_double_redir(char *line, int i)` | Checks for >> or << |
| `lexer_utils.c` | `int is_space(char c)` | Checks if character is whitespace |
| `lexer_utils.c` | `int is_redir(char c)` | Checks if character is redirection operator |
| `lexer_utils.c` | `int is_operator(char c)` | Checks if character is pipe or redir |

**Key Rules:**
- Quotes are kept in tokens for later expansion
- Redirections are separate tokens
- Whitespace separates tokens (unless quoted)

---

### 2. PARSER Module (`src/parser/`)
**Purpose:** Converts tokens into command structures.

| File | Function | Purpose |
|------|----------|---------|
| `parser.c` | `t_cmd *parse_tokens(t_token *tokens)` | Main parser - creates command list |
| `parser_single_cmd.c` | `t_cmd *parse_single_cmd(t_token **tokens)` | Parses single command |
| `parser_utils.c` | `char **tokens_to_argv(t_token *start)` | Converts tokens to argv array |
| `parser_redir.c` | `t_redir *new_redir(t_token_type type, char *target)` | Creates redirection struct |
| `parser_redir.c` | `void add_redir(t_redir **lst, t_redir *new)` | Adds redirection to list |
| `parser_redir.c` | `t_token *parse_redir(t_cmd *cmd, t_token *tok)` | Parses redirection token |
| `parser_redir.c` | `int is_redir_token(t_token_type type)` | Checks if token is redirection |

**Key Rules:**
- Stops parsing at pipes (they create separate commands)
- Collects all non-redir tokens into argv
- Maintains order of redirections

---

### 3. EXPANDER Module (`src/expander/`)
**Purpose:** Expands variables and handles quotes.

| File | Function | Purpose |
|------|----------|---------|
| `expander.c` | `char *expand_word(char *word, t_shell *shell)` | Expands single word |
| `expander_cmds.c` | `void expand_cmds(t_cmd *cmds, t_shell *shell)` | Main expander - expands all commands |
| `expander.c` | `static void handle_quotes(char word_char, t_state *state)` | Manages quote state |
| `expander.c` | `static char *process_word_char(t_expand_ctx *ctx, t_shell *shell)` | Processes one character |
| `expander_utils.c` | `char *append_char(char *s, char c)` | Appends character to string |
| `expander_var.c` | `char *expand_variable(char *res, char *word, int *i, t_shell *shell)` | Expands $VAR or $? |
| `expander_utils.c` | `char *strip_quotes(char *s)` | Removes outer quotes from string |
| `heredoc.c` | `void read_heredoc(char *delimiter, t_shell *shell, int fd)` | Reads heredoc input |
| `heredoc.c` | `int heredoc_should_expand(char *delimiter)` | Checks if heredoc needs expansion |
| `heredoc_signal.c` | `void setup_heredoc_sigaction(struct sigaction *old)` | Sets SIGINT behavior in heredoc |
| `heredoc_utils.c` | `char *heredoc_expand_line(char *line, t_shell *shell)` | Expands variables in heredoc |

**Key Rules:**
- Single quotes prevent ALL expansion (literal)
- Double quotes allow $ expansion only
- Quotes are removed from output
- Variables must start with letter/underscore

**Quote Handling (Fixed):**
- Single quotes inside double quotes are literal: `"it's"` → `it's` (not `it`)
- Double quotes inside single quotes are literal: `'say "hi"'` → `say "hi"` (not `say ""`)

---

### 4. EXECUTOR Module (`src/executor/`)
**Purpose:** Executes commands with redirections and pipes.

| File | Function | Purpose |
|------|----------|---------|
| `executor_utils.c` | `void execute_cmds(t_cmd *cmds, t_shell *shell)` | Main executor dispatcher |
| `executor_pipeline.c` | `void execute_pipeline(t_cmd *cmds, t_shell *shell)` | Handles pipe chains |
| `executor.c` | `void execute_single_cmd(t_cmd *cmd, t_shell *shell)` | Executes single command |
| `executor_exec.c` | `void execve_or_builtin(t_cmd *cmd, t_shell *shell, t_cmd *cmds_root)` | Routes to builtin or execve |
| `executor_utils.c` | `char *get_env_value(char **envp, char *name)` | Gets environment variable value |
| `executor_utils.c` | `char *find_command_path(char *cmd, t_shell *shell)` | Finds command in PATH |
| `executor_redirections.c` | `int apply_redirections(t_redir *redirs, t_shell *shell)` | Applies all redirections |
| `executor_heredoc.c` | `void process_heredocs(t_cmd *cmds, t_shell *shell)` | Pre-processes all heredocs |
| `executor_heredoc_apply.c` | `int apply_heredoc(char *delimiter, t_shell *shell)` | Creates heredoc stream |
| `executor_heredoc.c` | `void close_heredoc_fds(t_cmd *cmds)` | Cleanup heredoc files |

**Key Rules:**
- Child process for external commands
- Parent handles pipes and file descriptors
- Redirections applied in child before execve
- Heredocs processed before execution

---

### 5. BUILTIN Module (`src/builtin/`)
**Purpose:** Implements shell built-in commands.

| File | Function | Purpose | Notes |
|------|----------|---------|-------|
| `builtin.c` | `int is_builtin(char *cmd)` | Checks if command is builtin | |
| `builtin.c` | `int run_builtin(t_cmd *cmd, t_shell *shell)` | Executes builtin | Returns exit code |
| `builtin_echo.c` | `void builtin_echo(char **argv)` | echo command | Handles -n flag |
| `builtin_pwd.c` | `void builtin_pwd(void)` | pwd command | |
| `builtin_cd.c` | `int builtin_cd(char **argv, t_shell *shell)` | cd command | Updates OLDPWD, PWD |
| `builtin_env.c` | `void builtin_env(t_shell *shell)` | env command | Prints environment |
| `builtin_exit.c` | `int builtin_exit(char **argv, t_shell *shell)` | exit command | Custom exit codes |
| `builtin_export.c` | `int builtin_export(t_shell *shell, char **argv)` | export command | Exports variables |
| `builtin_unset.c` | `int builtin_unset(char **argv, t_shell *shell)` | unset command | Removes variables |
| `export_helpers.c` | `int is_valid_identifier(char *s)` | Validates var names | |
| `export_helpers.c` | `int find_env_index(char **envp, char *key)` | Finds env variable | |
| `export_utils.c` | `void export_var(t_shell *shell, char *arg)` | Exports single variable | <25 lines |
| `export_helpers.c` | `void env_add(t_shell *shell, char *new_var)` | Adds to environment | |
| `export_helpers.c` | `void env_replace(char **envp, int index, char *new_var)` | Updates env var | |
| `export_utils.c` | `void print_export_env(t_shell *shell)` | Prints export format | |
| `export_env_dup.c` | `char **env_dup(char **envp)` | Duplicates env array | |
| `export_new_var.c` | `void export_new_var(t_shell *shell, char *arg)` | Adds export without '=' | |

**Key Rules:**
- Built-ins run in parent shell (affect environment)
- External commands run in child process
- Exit code stored in `shell->exit_code`

---

### 6. Utility Modules

#### `src/main.c`
```c
void prompt_loop(t_shell *shell)     // Main interactive loop
// Global: volatile sig_atomic_t g_signal  // Signal tracking
```

#### `src/prompt.c`
```c
void prompt_loop(t_shell *shell)                           // Main interactive loop
static int handle_signal_interrupt(t_shell *shell, char **line)  // Handles Ctrl+C signal
static void process_input(char *line, t_shell *shell)      // Process single command input
```

#### `src/signal.c`
```c
void init_signals(void)              // Setup signal handlers
void reset_signals_in_child(void)    // Child process signal reset
static void sigint_handler(int sig)  // SIGINT handler (Ctrl+C)
```

#### `src/env_utils.c`
```c
char **copy_envp(char **envp)        // Duplicates environment
void free_envp(char **envp)          // Frees environment copy
void update_env_var(t_shell *shell, char *name, char *value)  // Updates env var
void env_remove_at_index(t_shell *shell, int index)           // Removes env var
```

---

## Coding Standards

### Naming Conventions
```c
// Functions: snake_case
void execute_commands(t_cmd *cmds)
char *get_env_value(char **envp, char *name)

// Structs: s_ prefix with typedef
typedef struct s_token { ... } t_token;

// Enums: e_ prefix with typedef
typedef enum e_state { ... } t_state;

// Typedefs: _type suffix
typedef struct s_token *t_token;
```

### Function Rules
1. **Single responsibility** - one function does one thing
2. **<26 lines** - functions should be concise
3. **Return values** - 0 for success, 1 for error (builtins)
4. **Documentation** - complex logic needs comments
5. **Memory safety** - free all allocations, check NULL

### Code Style
```c
// Indentation: tabs (size 4)
if (condition)
{
    statement;
}

// Space before braces
if (x)
    single_statement;

// Pointer style
char *str;      // asterisk with type
void *ptr;

// Variable declarations at function start
int i;
char *temp;
```

### Memory Management
```c
// Always check malloc
ptr = malloc(size);
if (!ptr)
    return ;

// Free in reverse order of allocation
free(str);
free(ptr);

// Free arrays
free_split(arr);  // Use helper function

// NULL after free (defensive)
free(ptr);
ptr = NULL;
```

---

## Building & Testing

### Compilation
```bash
cd /path/to/minishell
make              # Build
make clean        # Remove objects
make fclean       # Remove all built files
make re           # Rebuild
```

### Testing Commands
```bash
# Basic tests
echo "hello" | ./minishell
echo "export TEST=value" | ./minishell
echo "pwd" | ./minishell

# Pipe test
echo "echo hello | cat" | ./minishell

# Redirection test
echo "echo test > /tmp/test.txt" | ./minishell
cat /tmp/test.txt

# Heredoc test
echo -e "cat << EOF\nhello\nEOF" | ./minishell

# Quote tests
echo 'echo "it'"'"'s working"' | ./minishell  # Should print: it's working
```

### Debug Output
```bash
# Uncomment debug functions in src/debug.c
// print_tokens(tokens);
// print_cmds(cmds);
```

---

## Common Modifications

### Adding a New Built-in Command

1. **Add function in `src/builtin/builtin_yourcommand.c`:**
```c
int builtin_yourcommand(char **argv, t_shell *shell)
{
    // Implementation max 25 lines
    shell->exit_code = 0;  // or 1 for error
    return (shell->exit_code);
}
```

2. **Add prototype in `includes/minishell.h`:**
```c
int builtin_yourcommand(char **argv, t_shell *shell);
```

3. **Add to `is_builtin()` in `src/builtin/builtin.c`:**
```c
if (ft_strcmp(cmd, "yourcommand") == 0)
    return (1);
```

4. **Add to `run_builtin()` in `src/builtin/builtin.c`:**
```c
if (ft_strcmp(cmd->argv[0], "yourcommand") == 0)
    return (builtin_yourcommand(cmd->argv, shell));
```

5. **Test:**
```bash
make
./minishell
> yourcommand arg1 arg2
```

### Modifying Quote Handling

Quote logic is in **`src/expander/expander.c`** in function `process_word_char()`:

```c
static char *process_word_char(char *res, char *word, int *i,
    t_state *state, t_shell *shell)
{
    // Single quotes only toggle when NOT in double quotes
    if (word[*i] == '\'' && *state != STATE_IN_DOUBLE_QUOTE)
    {
        handle_quotes(word[*i], state);
        (*i)++;
    }
    // Double quotes only toggle when NOT in single quotes
    else if (word[*i] == '"' && *state != STATE_IN_SINGLE_QUOTE)
    {
        handle_quotes(word[*i], state);
        (*i)++;
    }
    // ... rest of logic
}
```

### Modifying Redirection Behavior

Redirections are applied in **`src/executor/executor_redirections.c`** in `apply_redirections()`:

```c
int apply_redirections(t_redir *redirs, t_shell *shell)
{
    while (redirs)
    {
        if (redirs->type == T_REDIR_OUT)      // >
            fd = open(redirs->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        else if (redirs->type == T_REDIR_APPEND)  // >>
            fd = open(redirs->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
        
        dup2(fd, redirs->type == T_REDIR_OUT ? 1 : 0);
        close(fd);
        redirs = redirs->next;
    }
}
```

### Adding Variable Expansion

Variable expansion happens in **`src/expander/expander_var.c`** in `expand_variable()`:

```c
char *expand_variable(char *res, char *word, int *i, t_shell *shell)
{
    // Extract variable name
    // Look up in shell->envp_copy
    // Append value to result
}
```

---

## Project Statistics

- **Total Lines:** ~2,500 (source only)
- **Modules:** 6 (lexer, parser, expander, executor, builtin, utils)
- **Functions:** ~80
- **Data Structures:** 5 main structs
- **Built-ins:** 7 (echo, pwd, cd, env, export, unset, exit)

---

## Final Session Summary (Jan 23, 2026)

### Issues Fixed
1. **Valgrind Invalid Reads** - Safeguarded `split_argv_if_needed()` in expander to handle empty splits.
2. **Segfault in Parser** - Fixed safe pointer advancement in `fill_argv_only()` for redirection handling.
3. **Exit Codes** - Implemented exit code 2 for syntax errors (unclosed quotes, invalid pipes) in `prompt.c`.
4. **Signal Handling** - Removed redundant newlines on Ctrl+C; implemented heredoc-specific SIGINT handler with `read()` loop replacing `readline()` for robust EINTR handling.
5. **Heredoc Interruption** - Executor now aborts with exit code 130 on SIGINT during heredoc processing.
6. **Nested Minishell** - Verified proper signal handling and EOF behavior (Ctrl+D) in nested shells.
7. **Norminette Compliance:**
   - Added 42 headers to all files
   - Normalized indentation (tabs vs spaces)
   - Fixed TOO_MANY_ARGS: refactored `process_token_char()` with context struct
   - Fixed TOO_MANY_LINES: refactored functions to max 25 lines:
     - `prompt.c`: split `process_input()` into `cleanup_and_exit()`, `execute_parsing_and_execution()`
     - `heredoc.c`: split into `read_char_to_line()`, `handle_heredoc_line()`, `process_heredoc_line()`
     - `builtin_exit.c`: split into `validate_and_set_exit_code()`, `handle_invalid_arg()`

### Key Code Changes
- **src/expander/expander.c**: Guard split results in `split_argv_if_needed()`.
- **src/parser/parser_utils.c**: Safe token advancement in `fill_argv_only()`.
- **src/prompt.c**: Exit code 2 on lexer/parser errors; refactored for Norminette compliance.
- **src/signal.c**: Readline-compatible signal handler; no redundant newlines.
- **src/expander/heredoc.c**: `read()`-based line reader for immediate SIGINT response; refactored to multiple small functions.
- **src/executor/executor.c**: Abort paths after heredoc SIGINT; close FDs properly.
- **src/lexer/lexer.c**: Refactored `process_token_char()` with context struct to satisfy TOO_MANY_ARGS rule.
- **src/builtin/builtin_exit.c**: Refactored to split validation and error handling.

### Testing Validation
- ✅ Valgrind: No invalid reads on quoted inputs ('       ', "", etc.)
- ✅ Exit codes: 2 on syntax errors, 130 on Ctrl+C, 131 on Ctrl+\, 0 on normal EOF
- ✅ Nested minishells: Signal handling and EOF confirmed via manual TTY tests
- ✅ Pipe validation: Syntax errors for |, || patterns, pipes at edges
- ✅ Heredoc SIGINT: User confirmed Ctrl+C → exit 130; Ctrl+D → exit 0
- ✅ Functional tests: echo, pwd, export, variable expansion all working correctly

### Build Status
- **Compilation**: ✅ Clean (no warnings/errors)
- **Norminette**: ✅ Headers added; TOO_MANY_ARGS fixed; TOO_MANY_LINES refactored; indentation normalized
- **Functionality**: ✅ All features working post-refactoring

### Cleanup
- Removed all temporary test scripts (`test_*.sh`, `debug_*.sh`)
- Cleaned up debug and error logs
- Organized documentation

---

## Quick Reference

| Task | File | Function |
|------|------|----------|
| Add command | `src/builtin/builtin_cmd.c` | `builtin_cmd()` |
| Fix parsing | `src/parser/parser.c` | `parse_tokens()` |
| Modify quotes | `src/expander/expander.c` | `process_word_char()` |
| Change expansion | `src/expander/expander_var.c` | `expand_variable()` |
| Handle redirections | `src/executor/executor_redirections.c` | `apply_redirections()` |
| Modify pipes | `src/executor/executor_pipeline.c` | `execute_pipeline()` |

---

## Notes for Collaborators

1. **Test before submitting** - Run multiple test cases
2. **Keep functions small** - Max 25 lines for builtins
3. **Handle errors gracefully** - Check NULL pointers
4. **Don't modify libft** - It's a utility library
5. **Maintain modularity** - Don't create dependencies between modules
6. **Signal Safety** - Use only async-signal-safe functions in handlers
7. **Heredoc SIGINT** - Handled via `read()` loop; respects EINTR for immediate interrupts
8. **Test edge cases:**
   - Empty strings: `""`
   - Quote combinations: `"it's"`
   - Variables in quotes: `"$HOME"`
   - Pipe chains: `cmd1 | cmd2 | cmd3`
   - Redirections: `cmd > file`
   - Heredocs: `cat << EOF` (test Ctrl+C and Ctrl+D)
   - Nested shells: `./minishell` inside `./minishell`

---

Last Updated: 2026-01-23
