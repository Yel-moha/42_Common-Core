# Manual Signal Testing Guide for Minishell

## Signal Tests (Must be done manually)

### Test 1: ctrl-C in empty prompt
**Action:** Launch minishell, press Ctrl+C
**Expected:** New line with new prompt displayed
**Status:** ⬜ Not tested yet

### Test 2: ctrl-\ in empty prompt  
**Action:** Launch minishell, press Ctrl+\
**Expected:** Nothing happens (no quit, no output)
**Status:** ⬜ Not tested yet

### Test 3: ctrl-D in empty prompt
**Action:** Launch minishell, press Ctrl+D
**Expected:** Minishell quits (like bash)
**Status:** ⬜ Not tested yet

### Test 4: ctrl-C after typing text
**Action:** Type some text (don't press enter), press Ctrl+C
**Expected:** New line with new prompt, buffer cleared
**Test:** Press Enter after Ctrl+C to confirm buffer is clean
**Status:** ⬜ Not tested yet

### Test 5: ctrl-D after typing text
**Action:** Type some text (don't press enter), press Ctrl+D
**Expected:** Nothing happens
**Status:** ⬜ Not tested yet

### Test 6: ctrl-\ after typing text
**Action:** Type some text (don't press enter), press Ctrl+\
**Expected:** Nothing happens
**Status:** ⬜ Not tested yet

### Test 7: ctrl-C during blocking command (cat)
**Action:** Run `cat` (no args), press Ctrl+C
**Expected:** Cat terminates, new prompt appears
**Status:** ⬜ Not tested yet

### Test 8: ctrl-\ during blocking command (cat)
**Action:** Run `cat` (no args), press Ctrl+\
**Expected:** Cat terminates with "Quit (core dumped)", new prompt
**Status:** ⬜ Not tested yet

### Test 9: ctrl-D during blocking command (cat)
**Action:** Run `cat` (no args), press Ctrl+D
**Expected:** Cat receives EOF and exits normally
**Status:** ⬜ Not tested yet

### Test 10: ctrl-C during blocking command (grep)
**Action:** Run `grep "something"` (no file), press Ctrl+C
**Expected:** Grep terminates, new prompt appears
**Status:** ⬜ Not tested yet

## Global Variables Check

**Question:** How many global variables are used?
**Answer:** We use 1 global variable: `g_signal`

**Why?**
- Signal handlers cannot access local variables or pass parameters
- When a signal (SIGINT/Ctrl+C) is received, the signal handler needs to communicate with the main program
- `g_signal` stores the signal number (SIGINT) so the main loop can detect it and handle it appropriately
- This is the standard approach in C for signal handling when you need to interrupt blocking operations

**Example:**
```c
// When user presses Ctrl+C during readline():
// 1. Signal handler sets g_signal = SIGINT
// 2. Main loop checks g_signal after readline returns
// 3. If g_signal is set, display new prompt and reset it
```

This is **mandatory** because:
- Signal handlers run asynchronously (at any moment)
- They cannot return values to the caller
- They must be async-signal-safe (limited functions allowed)
- Global variables are the standard way to communicate between signal handler and main program

## Additional Edge Cases

### Empty/Whitespace Commands
✅ Empty command (just Enter) - Handled
✅ Only spaces - Handled  
✅ Only tabs - Handled

### Exit with Arguments
✅ `exit` - Works
✅ `exit 0` - Works
✅ `exit 42` - Works (returns 42)
✅ `exit 1 2 3` - Shows error "too many arguments"

### Return Values ($?)
✅ Successful command → $? = 0
✅ Failed command → $? = 2 (ls nonexistent)
✅ /bin/false → $? = 1
✅ /bin/true → $? = 0

### Quotes
✅ Double quotes preserve spaces
✅ Double quotes expand variables
✅ Single quotes preserve everything (no expansion)
✅ Single quotes show literal $USER
✅ Empty quotes work

### Builtins
✅ echo with -n flag
✅ echo with multiple -n flags
✅ export creates/modifies variables
✅ export without value (declare -x VAR)
✅ unset removes variables
✅ cd with absolute/relative paths
✅ cd with .. and .
✅ cd without args (goes to HOME)
✅ pwd in different directories
✅ env displays environment

### Redirections
✅ Output redirection (>)
✅ Append redirection (>>)
✅ Input redirection (<)
✅ Heredoc (<<)

### Pipes
✅ Simple pipes (echo | cat)
✅ Multiple pipes (cat | cat | cat)
✅ Pipes with grep
✅ Pipes with failed commands
✅ Pipes with redirections

### PATH
✅ Commands without path (ls, echo, cat)
✅ Commands with absolute path (/bin/ls)
✅ Commands with relative path (../bin/ls)

## Summary

**Automated Tests Passed:** All basic functionality ✅
**Manual Tests Required:** Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
**Memory Leaks:** None (0 bytes definitely lost) ✅
**Segfaults:** None ✅
**Core Functionality:** Working ✅
