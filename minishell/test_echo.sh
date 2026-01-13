#!/bin/bash
cd /home/yel-moha/github/42_Common-Core/minishell
make clean && make
echo "=== Testing echo ==="
echo -e "echo hello\nexit" | ./minishell
echo "=== Testing pwd ==="
echo -e "pwd\nexit" | ./minishell
