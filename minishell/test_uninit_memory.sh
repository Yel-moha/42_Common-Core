#!/bin/bash
# Test for conditional jump/uninitialized value errors

echo "=========================================="
echo "VALGRIND: Uninitialized Memory Detection"
echo "=========================================="
echo ""
echo "Testing for 'Conditional jump or move depends on uninitialised value'"
echo ""

# Test 1: Basic commands
echo "TEST 1: Basic commands"
echo "======================"
valgrind --leak-check=no --track-origins=yes --show-error-list=yes \
./minishell << 'EOF' 2>&1 | grep -A 5 "Conditional\|uninitialised\|Uninitialised"
pwd
echo hello
ls
exit
EOF

echo ""
echo ""

# Test 2: Variable expansion
echo "TEST 2: Variable expansion"
echo "=========================="
valgrind --leak-check=no --track-origins=yes \
./minishell << 'EOF' 2>&1 | grep -A 5 "Conditional\|uninitialised\|Uninitialised"
echo $HOME
echo $PATH
echo $USER
echo $?
exit
EOF

echo ""
echo ""

# Test 3: Quote handling
echo "TEST 3: Quote handling"
echo "======================"
valgrind --leak-check=no --track-origins=yes \
./minishell << 'EOF' 2>&1 | grep -A 5 "Conditional\|uninitialised\|Uninitialised"
echo "test"
echo 'test'
echo "it's working"
echo 'say "hi"'
exit
EOF

echo ""
echo ""

# Test 4: Redirections
echo "TEST 4: Redirections"
echo "===================="
valgrind --leak-check=no --track-origins=yes \
./minishell << 'EOF' 2>&1 | grep -A 5 "Conditional\|uninitialised\|Uninitialised"
echo test > /tmp/vg_test.txt
cat < /tmp/vg_test.txt
echo append >> /tmp/vg_test.txt
exit
EOF

echo ""
echo ""

# Test 5: Pipes
echo "TEST 5: Pipes"
echo "============="
valgrind --leak-check=no --track-origins=yes \
./minishell << 'EOF' 2>&1 | grep -A 5 "Conditional\|uninitialised\|Uninitialised"
echo hello | cat
echo test | cat | cat
exit
EOF

echo ""
echo ""

# Test 6: Heredocs
echo "TEST 6: Heredocs"
echo "================"
valgrind --leak-check=no --track-origins=yes \
./minishell << 'EOF' 2>&1 | grep -A 5 "Conditional\|uninitialised\|Uninitialised"
cat << END
line1
line2
END
exit
EOF

echo ""
echo ""

# Test 7: Export/Unset
echo "TEST 7: Export/Unset"
echo "===================="
valgrind --leak-check=no --track-origins=yes \
./minishell << 'EOF' 2>&1 | grep -A 5 "Conditional\|uninitialised\|Uninitialised"
export TEST=value
export TEST2
unset TEST
exit
EOF

echo ""
echo ""

# Test 8: Error conditions
echo "TEST 8: Error conditions"
echo "========================"
valgrind --leak-check=no --track-origins=yes \
./minishell << 'EOF' 2>&1 | grep -A 5 "Conditional\|uninitialised\|Uninitialised"
nonexistent_command
/bin/false
cat nonexistent_file.txt
exit
EOF

echo ""
echo ""

# Test 9: Empty/edge cases
echo "TEST 9: Edge cases"
echo "=================="
valgrind --leak-check=no --track-origins=yes \
./minishell << 'EOF' 2>&1 | grep -A 5 "Conditional\|uninitialised\|Uninitialised"
echo ""
echo ''
export A=
unset NONEXISTENT
exit
EOF

echo ""
echo ""

echo "=========================================="
echo "FULL DETAILED RUN"
echo "=========================================="
echo "Running one command with full Valgrind output..."
echo ""

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
         --verbose --show-error-list=yes \
./minishell << 'EOF'
echo "Testing for uninitialized memory"
export TEST=value
echo $TEST
exit
EOF

echo ""
echo "=========================================="
echo "If you see 'Conditional jump or move depends on uninitialised value',"
echo "look for the 'by 0x...' addresses to identify which function has the issue."
echo "Common causes:"
echo "  - Using malloc without initializing (use calloc or memset)"
echo "  - Reading beyond string null terminator"
echo "  - Not initializing struct members"
echo "  - Using variables before assigning them"
echo "=========================================="

# Cleanup
rm -f /tmp/vg_test.txt
