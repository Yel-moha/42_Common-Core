#!/bin/bash
# Valgrind FD tracking test

echo "=== Valgrind FD Leak Detection ==="
echo ""
echo "This is the most accurate way to detect FD leaks."
echo ""

valgrind --leak-check=full --track-fds=yes --trace-children=yes ./minishell << 'EOF'
echo "Test 1: Multiple redirections"
echo a > /tmp/t1.txt
echo b > /tmp/t2.txt
echo c > /tmp/t3.txt
echo "Test 2: Pipes"
echo test | cat
echo test | cat
echo "Test 3: Heredocs"
cat << END
test
END
exit
EOF

echo ""
echo "==="
echo "Look for 'FILE DESCRIPTORS: X open at exit' in the output above."
echo "Should be 4 (0=stdin, 1=stdout, 2=stderr, 4=readline history file)"
echo "If more than 4, you have FD leaks!"
echo "==="

# Cleanup
rm -f /tmp/t*.txt
