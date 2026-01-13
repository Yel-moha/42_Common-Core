#!/bin/bash
# Comprehensive conditional jump test

echo "=============================================="
echo "COMPREHENSIVE VALGRIND CONDITIONAL JUMP TEST"
echo "=============================================="
echo ""

# Save test results
RESULTS="/tmp/valgrind_results.txt"
rm -f $RESULTS

run_test() {
    local test_name="$1"
    local commands="$2"
    
    echo "Testing: $test_name"
    echo "Testing: $test_name" >> $RESULTS
    
    valgrind --leak-check=no --track-origins=yes --error-limit=no \
    ./minishell 2>&1 <<EOF | grep -c "Conditional jump\|uninitialised" >> $RESULTS
$commands
exit
EOF
    
    count=$(tail -1 $RESULTS)
    if [ "$count" -eq "0" ]; then
        echo "  ✓ PASS (0 errors)"
    else
        echo "  ✗ FAIL ($count errors)"
        echo "    Run manually to see details:"
        echo "    valgrind --track-origins=yes ./minishell"
    fi
    echo ""
}

echo "Running systematic tests..."
echo ""

# Test 1: Basic initialization
run_test "Empty command" ""

# Test 2: Simple echo
run_test "Simple echo" "echo hello"

# Test 3: Variable expansion
run_test "Variable expansion" "echo \$HOME"

# Test 4: Exit code
run_test "Exit code expansion" "echo \$?"

# Test 5: Single quotes
run_test "Single quotes" "echo 'test'"

# Test 6: Double quotes
run_test "Double quotes" 'echo "test"'

# Test 7: Mixed quotes
run_test "Mixed quotes" 'echo "it'\''s working"'

# Test 8: Pipe
run_test "Simple pipe" "echo test | cat"

# Test 9: Redirection output
run_test "Output redirection" "echo test > /tmp/vg_out.txt"

# Test 10: Redirection input
run_test "Input redirection" "cat < /etc/hostname"

# Test 11: Append
run_test "Append redirection" "echo test >> /tmp/vg_out.txt"

# Test 12: Heredoc
run_test "Heredoc" 'cat << EOF
line1
line2
EOF'

# Test 13: Export
run_test "Export variable" "export TEST=value"

# Test 14: Export without value
run_test "Export without value" "export TEST"

# Test 15: Unset
run_test "Unset variable" "unset PATH"

# Test 16: Builtin pwd
run_test "Builtin pwd" "pwd"

# Test 17: Builtin cd
run_test "Builtin cd" "cd /tmp"

# Test 18: Builtin env
run_test "Builtin env" "env"

# Test 19: Failed command
run_test "Failed command" "nonexistent_cmd"

# Test 20: Multiple pipes
run_test "Multiple pipes" "echo test | cat | cat | cat"

# Test 21: Complex command
run_test "Complex redirection" "cat < /etc/hostname > /tmp/vg_out.txt"

# Test 22: Empty variable
run_test "Empty variable" "export EMPTY="

# Test 23: Multiple redirections
run_test "Multiple redirections" 'echo a > /tmp/t1.txt
echo b > /tmp/t2.txt
echo c > /tmp/t3.txt'

# Test 24: Pipe with redirection
run_test "Pipe with redirection" "echo test | cat > /tmp/vg_out.txt"

# Test 25: Heredoc with pipe
run_test "Heredoc with pipe" 'cat << EOF | grep test
test line
other line
EOF'

echo ""
echo "=============================================="
echo "SUMMARY"
echo "=============================================="
echo ""

total_errors=$(grep -o "FAIL" $RESULTS | wc -l)
total_tests=$(grep -c "Testing:" $RESULTS)

echo "Total tests: $total_tests"
echo "Failed tests: $total_errors"
echo ""

if [ "$total_errors" -eq "0" ]; then
    echo "✓✓✓ ALL TESTS PASSED - NO CONDITIONAL JUMPS ✓✓✓"
else
    echo "⚠ SOME TESTS FAILED - SEE DETAILS ABOVE ⚠"
    echo ""
    echo "To debug, run:"
    echo "  valgrind --track-origins=yes ./minishell"
    echo ""
    echo "Then manually type the failing command."
    echo "Valgrind will show the exact line causing the issue."
fi

echo ""
echo "Full results saved to: $RESULTS"
echo ""

# Cleanup
rm -f /tmp/vg_out.txt /tmp/t*.txt

# If you want detailed output for one specific test:
echo "=============================================="
echo "DETAILED RUN - SINGLE COMMAND"
echo "=============================================="
echo ""
echo "Running with full details..."
echo ""

valgrind --leak-check=full --track-origins=yes --show-error-list=yes \
./minishell << 'EOF' 2>&1 | grep -A 10 "Conditional\|uninitialised\|ERROR SUMMARY"
echo "test command with quotes"
exit
EOF

echo ""
echo "If ERROR SUMMARY shows >0 errors, look above for details."
