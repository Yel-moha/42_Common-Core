#!/bin/bash
# Test for file descriptor leaks

echo "=== FD Leak Test Suite ==="
echo ""

# Start minishell in background and get PID
(sleep 1; echo "pwd") | ./minishell &
MINISHELL_PID=$!
sleep 0.5

echo "1. Initial FD count:"
ls -la /proc/$MINISHELL_PID/fd 2>/dev/null | wc -l

# Wait for completion
wait $MINISHELL_PID

echo ""
echo "2. Testing multiple redirections..."
(
  sleep 0.2
  echo "echo test > /tmp/test1.txt"
  sleep 0.2
  echo "echo test > /tmp/test2.txt"
  sleep 0.2
  echo "echo test > /tmp/test3.txt"
  sleep 0.2
  echo "ls /proc/self/fd"
  sleep 0.2
  echo "exit"
) | ./minishell

echo ""
echo "3. Testing pipes..."
(
  sleep 0.2
  echo "echo hello | cat | cat | cat"
  sleep 0.2
  echo "ls /proc/self/fd"
  sleep 0.2
  echo "exit"
) | ./minishell

echo ""
echo "4. Testing heredocs..."
(
  sleep 0.2
  echo "cat << EOF"
  echo "line1"
  echo "line2"
  echo "EOF"
  sleep 0.2
  echo "cat << EOF"
  echo "line3"
  echo "EOF"
  sleep 0.2
  echo "ls /proc/self/fd"
  sleep 0.2
  echo "exit"
) | ./minishell

echo ""
echo "5. Testing failed commands..."
(
  sleep 0.2
  echo "nonexistent_command"
  sleep 0.2
  echo "another_bad_cmd"
  sleep 0.2
  echo "ls /proc/self/fd"
  sleep 0.2
  echo "exit"
) | ./minishell

echo ""
echo "6. Testing mixed redirections and pipes..."
(
  sleep 0.2
  echo "cat < /etc/hostname | grep . > /tmp/out.txt"
  sleep 0.2
  echo "ls /proc/self/fd"
  sleep 0.2
  echo "exit"
) | ./minishell

echo ""
echo "=== Tests Complete ==="
echo "Check that FD counts remain stable (should be 0, 1, 2, 255 for bash, similar for minishell)"

# Cleanup
rm -f /tmp/test1.txt /tmp/test2.txt /tmp/test3.txt /tmp/out.txt
