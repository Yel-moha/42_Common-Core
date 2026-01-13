#!/bin/bash
# Manual FD Leak Detection Tests
# Run these commands in your minishell and check /proc/self/fd

echo "======================================"
echo "FD LEAK DETECTION - MANUAL TESTS"
echo "======================================"
echo ""
echo "In each test, run 'ls -la /proc/self/fd' and count the FDs."
echo "Typical shell should have: 0 (stdin), 1 (stdout), 2 (stderr), and possibly 255 (bash internal)"
echo ""
echo "If FDs keep increasing with each command, you have a leak!"
echo ""

cat << 'EOF'

TEST 1: Multiple Output Redirections
-------------------------------------
minishell$ echo test1 > /tmp/t1.txt
minishell$ echo test2 > /tmp/t2.txt
minishell$ echo test3 > /tmp/t3.txt
minishell$ ls -la /proc/self/fd
minishell$ echo test4 > /tmp/t4.txt
minishell$ ls -la /proc/self/fd

Expected: FD count should stay the same (3-4 FDs)
Problem: If count increases, you're not closing output files


TEST 2: Multiple Input Redirections
-------------------------------------
minishell$ cat < /etc/hostname
minishell$ cat < /etc/hostname
minishell$ cat < /etc/hostname
minishell$ ls -la /proc/self/fd

Expected: Same FD count as start
Problem: If count increases, input files aren't closed


TEST 3: Heredoc Stress Test
------------------------------
minishell$ cat << EOF
line1
line2
EOF
minishell$ cat << DELIM
line3
DELIM
minishell$ cat << END
line4
END
minishell$ ls -la /proc/self/fd

Expected: No extra FDs (heredoc temp files should be closed)
Problem: If you see extra FDs, heredoc cleanup is missing


TEST 4: Failed Command + Redirection
--------------------------------------
minishell$ nonexistent > /tmp/out.txt
minishell$ ls -la /proc/self/fd
minishell$ another_bad_cmd < /etc/hostname
minishell$ ls -la /proc/self/fd

Expected: No FD leak even when command fails
Problem: FDs not closed in error path


TEST 5: Pipe Chain
-------------------
minishell$ echo hello | cat | cat | cat | cat
minishell$ ls -la /proc/self/fd
minishell$ echo world | cat | cat | cat | cat
minishell$ ls -la /proc/self/fd

Expected: FD count returns to baseline after each pipe
Problem: Pipe FDs not closed in parent/children


TEST 6: Combined Redirections
-------------------------------
minishell$ cat < /etc/hostname > /tmp/out.txt
minishell$ cat < /etc/hostname >> /tmp/out.txt
minishell$ ls -la /proc/self/fd

Expected: Same FD count
Problem: Either input or output FDs leaking


TEST 7: Heredoc in Pipe
------------------------
minishell$ cat << EOF | grep test
test line
other line
test again
EOF
minishell$ ls -la /proc/self/fd

Expected: No extra FDs
Problem: Heredoc FD not passed/closed correctly


TEST 8: Multiple Commands Rapidly
-----------------------------------
Run this 10 times and check FD count grows:
minishell$ echo test > /tmp/test.txt; ls -la /proc/self/fd
minishell$ echo test > /tmp/test.txt; ls -la /proc/self/fd
minishell$ echo test > /tmp/test.txt; ls -la /proc/self/fd
(repeat...)

Expected: FD count stays constant
Problem: FDs accumulating with each command


TEST 9: Check with lsof (run from another terminal)
-----------------------------------------------------
# Get minishell PID
ps aux | grep minishell

# Monitor open files (run in another terminal while minishell runs)
watch -n 1 "lsof -p <PID> | grep -v mem | grep -v DEL"

# In minishell, run commands and watch for growing FD list
minishell$ echo test > /tmp/t1.txt
minishell$ echo test > /tmp/t2.txt
minishell$ cat << EOF
test
EOF

Expected: Only stdin/stdout/stderr remain between commands
Problem: File handles shown in lsof output that persist


TEST 10: Valgrind FD Tracking
-------------------------------
valgrind --track-fds=yes ./minishell

Then run commands and check output for:
"FILE DESCRIPTORS: X open at exit"

Where X should be low (just stdin, stdout, stderr)

EOF

echo ""
echo "======================================"
echo "AUTOMATED FD COUNT TEST"
echo "======================================"
echo ""
echo "This will run commands and show FD counts..."
echo ""

# Simple automated test
(
cat << 'TESTEOF'
ls -la /proc/self/fd
echo "--- After 5 redirections ---"
echo a > /tmp/t1.txt
echo b > /tmp/t2.txt
echo c > /tmp/t3.txt
echo d > /tmp/t4.txt
echo e > /tmp/t5.txt
ls -la /proc/self/fd
echo "--- After 3 heredocs ---"
cat << EOF1
line1
EOF1
cat << EOF2
line2
EOF2
cat << EOF3
line3
EOF3
ls -la /proc/self/fd
echo "--- After 3 pipes ---"
echo test | cat
echo test | cat
echo test | cat
ls -la /proc/self/fd
exit
TESTEOF
sleep 1
) | ./minishell

echo ""
echo "Compare the FD counts above. They should remain stable (around 3-5 FDs)."
echo ""
