#!/bin/bash
# Quick FD Leak Test

echo "=== Quick FD Leak Test ==="
echo ""
echo "Running test sequence and checking FD counts..."
echo ""

./minishell << 'EOF'
echo "Initial FD count:"
ls /proc/self/fd | wc -l
echo ""
echo "After 10 redirections:"
echo 1 > /tmp/t1.txt
echo 2 > /tmp/t2.txt
echo 3 > /tmp/t3.txt
echo 4 > /tmp/t4.txt
echo 5 > /tmp/t5.txt
echo 6 > /tmp/t6.txt
echo 7 > /tmp/t7.txt
echo 8 > /tmp/t8.txt
echo 9 > /tmp/t9.txt
echo 10 > /tmp/t10.txt
ls /proc/self/fd | wc -l
echo ""
echo "After 5 pipes:"
echo test | cat
echo test | cat
echo test | cat
echo test | cat
echo test | cat
ls /proc/self/fd | wc -l
echo ""
echo "After 5 heredocs:"
cat << E1
test1
E1
cat << E2
test2
E2
cat << E3
test3
E3
cat << E4
test4
E4
cat << E5
test5
E5
ls /proc/self/fd | wc -l
exit
EOF

echo ""
echo "All FD counts above should be the same (around 4-5)."
echo "If they increase, you have an FD leak!"
echo ""

# Cleanup
rm -f /tmp/t*.txt

echo "=== Best Test: Use Valgrind ==="
echo "Run: valgrind --track-fds=yes ./minishell"
echo "Then execute commands and check 'FILE DESCRIPTORS: X open at exit'"
echo "X should be 3 (or 4 with readline)"
