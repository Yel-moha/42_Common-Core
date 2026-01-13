#!/bin/bash
# Debug script for when you see conditional jumps at school

echo "=========================================="
echo "CONDITIONAL JUMP DEBUGGING HELPER"
echo "=========================================="
echo ""
echo "If you see conditional jump errors at school, follow these steps:"
echo ""

cat << 'GUIDE'

STEP 1: Identify the problem
-----------------------------
Run with maximum detail:

valgrind --leak-check=full \
         --track-origins=yes \
         --show-error-list=yes \
         --verbose \
         ./minishell

Then type commands one by one to see which triggers the error.


STEP 2: Common causes and fixes
--------------------------------

CAUSE 1: Uninitialized variables
   Problem: int i; if (i > 0) ...
   Fix: int i = 0;

CAUSE 2: malloc without initialization
   Problem: char *str = malloc(10); if (str[0] == 'a') ...
   Fix: char *str = calloc(10, 1); OR memset(str, 0, 10);

CAUSE 3: Uninitialized struct members
   Problem: t_token *tok = malloc(sizeof(t_token));
           if (tok->expand) ...
   Fix: tok->expand = 0; OR use calloc

CAUSE 4: Reading past string end
   Problem: while (str[i] != ' ') i++;  // no null check
   Fix: while (str[i] && str[i] != ' ') i++;

CAUSE 5: Array not initialized
   Problem: char buffer[100]; if (buffer[0]) ...
   Fix: char buffer[100] = {0}; OR memset(buffer, 0, 100);


STEP 3: Check these specific areas in your code
------------------------------------------------

□ lexer.c: Check state initialization
   t_state state = STATE_NORMAL;  ✓

□ parser.c: Check t_cmd initialization
   t_cmd *cmd = malloc(sizeof(t_cmd));
   cmd->argv = NULL;              ✓
   cmd->redirs = NULL;            ✓
   cmd->next = NULL;              ✓

□ expander.c: Check loop variables
   int i = 0;                     ✓

□ executor.c: Check pipe/fd variables
   int fd[2];
   int saved_stdin = -1;          ✓

□ builtin/*.c: Check return values initialized
   int result = 0;                ✓


STEP 4: Specific Valgrind flags to use
---------------------------------------

# Find exact line causing issue:
valgrind --track-origins=yes --read-var-info=yes ./minishell

# With line numbers (if compiled with -g):
valgrind --track-origins=yes --read-var-info=yes \
         --num-callers=20 ./minishell

# Generate suppressions (for readline noise):
valgrind --gen-suppressions=all ./minishell


STEP 5: Test specific modules
------------------------------

# Test only lexer:
echo "echo hello" | valgrind --track-origins=yes ./minishell

# Test only parser:
echo "echo hello | cat" | valgrind --track-origins=yes ./minishell

# Test only expander:
echo 'echo $HOME' | valgrind --track-origins=yes ./minishell

# Test only executor:
echo "ls" | valgrind --track-origins=yes ./minishell


STEP 6: Look for these patterns in Valgrind output
---------------------------------------------------

Pattern: "Conditional jump or move depends on uninitialised value(s)"
Location: "by 0x109ABC: function_name (file.c:42)"

This tells you:
  - Function: function_name
  - File: file.c
  - Line: 42

Go to that line and check if all variables are initialized!


STEP 7: Quick fixes checklist
------------------------------

Find all malloc calls and check if they should be calloc:
  grep -n "malloc" src/**/*.c

Find all variable declarations in conditions:
  grep -n "if.*{" src/**/*.c

Check all loop counters are initialized:
  grep -n "for\|while" src/**/*.c

Check all struct allocations:
  grep -n "t_token\|t_cmd\|t_redir" src/**/*.c


STEP 8: Compare with working version
-------------------------------------

If you get errors at school but not at home, differences might be:
  - Different Valgrind version (use --version)
  - Different compiler flags
  - Different environment size (causes different memory layout)
  - Different readline version

Test with exactly same flags as at school!


STEP 9: Create minimal reproduction
------------------------------------

If you find a problematic command:

echo "problematic_command" > test_case.txt
valgrind --track-origins=yes ./minishell < test_case.txt

This makes it easier to debug.

GUIDE

echo ""
echo "=========================================="
echo "RUNNING DIAGNOSTIC..."
echo "=========================================="
echo ""

# Quick diagnostic
echo "Checking for common issues..."
echo ""

echo "1. Checking for uninitialized state variables:"
grep -n "t_state state" src/**/*.c | head -5

echo ""
echo "2. Checking malloc vs calloc usage:"
echo "   malloc count: $(grep -r "malloc" src/**/*.c | wc -l)"
echo "   calloc count: $(grep -r "calloc" src/**/*.c | wc -l)"
echo "   (calloc is safer - initializes to 0)"

echo ""
echo "3. Checking struct initializations:"
grep -n "= malloc(sizeof(t_" src/**/*.c | head -5

echo ""
echo "4. Running quick Valgrind test:"
echo ""

valgrind --leak-check=no --track-origins=yes ./minishell 2>&1 << 'EOF' | \
grep "ERROR SUMMARY\|Conditional"
echo test
exit
EOF

echo ""
echo "=========================================="
echo "If you still see errors at school:"
echo "1. Save the exact Valgrind output"
echo "2. Note the exact command that triggers it"
echo "3. Check the function name in the error"
echo "4. Go to that function and initialize ALL variables"
echo "=========================================="
