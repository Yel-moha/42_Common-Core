#!/bin/bash
# Focused test to identify specific uninitialized memory issues

echo "=== TARGETED UNINITIALIZED MEMORY TEST ==="
echo ""

# Create test with suppressions to filter readline noise
cat > /tmp/minishell.supp << 'SUPP'
{
   readline_noise
   Memcheck:Cond
   ...
   obj:*/libreadline.so*
}
{
   readline_leak
   Memcheck:Leak
   ...
   obj:*/libreadline.so*
}
SUPP

echo "Testing each module separately..."
echo ""

# Test lexer
echo "1. LEXER TEST"
echo "-------------"
valgrind --suppressions=/tmp/minishell.supp --leak-check=no --track-origins=yes \
./minishell 2>&1 <<'EOF' | grep -B2 -A8 "Conditional\|uninitialised"
echo simple command
exit
EOF

echo ""
echo "2. PARSER TEST (complex input)"
echo "------------------------------"
valgrind --suppressions=/tmp/minishell.supp --leak-check=no --track-origins=yes \
./minishell 2>&1 <<'EOF' | grep -B2 -A8 "Conditional\|uninitialised"
echo test | cat > /tmp/out.txt
exit
EOF

echo ""
echo "3. EXPANDER TEST (variables)"
echo "----------------------------"
valgrind --suppressions=/tmp/minishell.supp --leak-check=no --track-origins=yes \
./minishell 2>&1 <<'EOF' | grep -B2 -A8 "Conditional\|uninitialised"
export VAR=test
echo $VAR
echo $?
exit
EOF

echo ""
echo "4. QUOTE HANDLING TEST"
echo "----------------------"
valgrind --suppressions=/tmp/minishell.supp --leak-check=no --track-origins=yes \
./minishell 2>&1 <<'EOF' | grep -B2 -A8 "Conditional\|uninitialised"
echo "double quotes"
echo 'single quotes'
echo "nested 'quotes'"
exit
EOF

echo ""
echo "5. FULL VALGRIND OUTPUT (first error only)"
echo "==========================================="
valgrind --suppressions=/tmp/minishell.supp --track-origins=yes --read-var-info=yes \
./minishell 2>&1 <<'EOF' | head -100
pwd
exit
EOF

echo ""
echo "=== COMMON SOURCES OF UNINITIALIZED MEMORY ==="
echo ""
echo "1. CHECK: Are all variables initialized before use?"
echo "2. CHECK: malloc() without memset/initialization?"
echo "3. CHECK: Reading past string end (missing null check)?"
echo "4. CHECK: Struct members initialized?"
echo "5. CHECK: Array indices initialized?"
echo ""
echo "Run: valgrind --track-origins=yes ./minishell"
echo "Then type commands manually to see exact line causing issue"
echo ""

rm -f /tmp/minishell.supp /tmp/out.txt
