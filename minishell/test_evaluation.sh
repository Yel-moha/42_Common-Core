#!/bin/bash

# Minishell Evaluation Test Script
# Based on 42 evaluation sheet

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0
TOTAL=0

print_test() {
    echo -e "\n${YELLOW}=== $1 ===${NC}"
}

run_test() {
    TOTAL=$((TOTAL + 1))
    echo -e "\n${YELLOW}Test $TOTAL: $1${NC}"
    echo "$2" | ./minishell 2>&1 | head -20
    if [ $? -eq 0 ]; then
        PASSED=$((PASSED + 1))
        echo -e "${GREEN}✓ Passed${NC}"
    else
        FAILED=$((FAILED + 1))
        echo -e "${RED}✗ Failed${NC}"
    fi
}

echo -e "${GREEN}Starting Minishell Evaluation Tests${NC}"
echo "Make sure minishell is compiled!"

# 1. Simple Command & Global Variables
print_test "1. Simple Command & Global Variables"
echo "Testing: /bin/ls"
echo -e "/bin/ls\nexit" | ./minishell
echo -e "\nTesting: Empty command"
echo -e "\nexit" | ./minishell
echo -e "\nTesting: Only spaces"
echo -e "   \nexit" | ./minishell
echo -e "\nTesting: Only tabs"
echo -e "\t\t\nexit" | ./minishell

# 2. Arguments
print_test "2. Arguments"
echo -e "/bin/ls -l\nexit" | ./minishell
echo -e "/bin/echo hello world\nexit" | ./minishell
echo -e "/bin/cat /etc/hostname\nexit" | ./minishell

# 3. echo
print_test "3. echo"
echo -e "echo\nexit" | ./minishell
echo -e "echo hello\nexit" | ./minishell
echo -e "echo hello world\nexit" | ./minishell
echo -e "echo -n hello\nexit" | ./minishell
echo -e "echo -n -n -n hello\nexit" | ./minishell
echo -e "echo -nnnn hello\nexit" | ./minishell

# 4. exit
print_test "4. exit"
echo -e "exit\n" | ./minishell
echo -e "exit 0\n" | ./minishell
echo -e "exit 42\n" | ./minishell
echo -e "exit 1 2 3\n" | ./minishell 2>&1 | head -5

# 5. Return value of a process
print_test "5. Return value of a process"
echo -e "/bin/ls\necho \$?\nexit" | ./minishell
echo -e "/bin/ls filethatdoesntexist\necho \$?\nexit" | ./minishell 2>&1
echo -e "/bin/false\necho \$?\nexit" | ./minishell
echo -e "/bin/true\necho \$?\nexit" | ./minishell

# 7. Double Quotes
print_test "7. Double Quotes"
echo -e 'echo "hello world"\nexit' | ./minishell
echo -e 'echo "hello   world"\nexit' | ./minishell
echo -e 'echo "cat lol.c | cat > lol.c"\nexit' | ./minishell
echo -e 'echo "test \$USER test"\nexit' | ./minishell

# 8. Single Quotes
print_test "8. Single Quotes"
echo -e "echo 'hello world'\nexit" | ./minishell
echo -e "echo '\$USER'\nexit" | ./minishell
echo -e "echo 'cat | grep | >'\nexit" | ./minishell
echo -e "echo ''\nexit" | ./minishell

# 9. env
print_test "9. env"
echo -e "env\nexit" | ./minishell | head -10

# 10. export
print_test "10. export"
echo -e "export TEST=hello\nenv | grep TEST\nexit" | ./minishell
echo -e "export TEST=hello\necho \$TEST\nexit" | ./minishell
echo -e "export TEST\nexport | grep TEST\nexit" | ./minishell

# 11. unset
print_test "11. unset"
echo -e "export TEST=hello\necho \$TEST\nunset TEST\necho \$TEST\nexit" | ./minishell
echo -e "unset PATH\necho \$PATH\nexit" | ./minishell

# 12. cd
print_test "12. cd"
echo -e "cd /tmp\npwd\nexit" | ./minishell
echo -e "cd ..\npwd\nexit" | ./minishell
echo -e "cd .\npwd\nexit" | ./minishell
echo -e "cd\npwd\nexit" | ./minishell
echo -e "cd /nonexistent\nexit" | ./minishell 2>&1 | head -5

# 13. pwd
print_test "13. pwd"
echo -e "pwd\nexit" | ./minishell
echo -e "cd /tmp\npwd\ncd ..\npwd\nexit" | ./minishell

# 14. Relative Path
print_test "14. Relative Path"
echo -e "mkdir -p /tmp/test_minishell/subdir\ncd /tmp/test_minishell/subdir\n../../../bin/ls /tmp\nexit" | ./minishell
rm -rf /tmp/test_minishell

# 15. Environment path
print_test "15. Environment PATH"
echo -e "ls\nexit" | ./minishell | head -5
echo -e "echo\nexit" | ./minishell
echo -e "cat\nexit" | ./minishell 2>&1 | head -5

# 16. Redirections
print_test "16. Redirections"
echo -e "echo hello > /tmp/test_out.txt\ncat /tmp/test_out.txt\nexit" | ./minishell
echo -e "echo world >> /tmp/test_out.txt\ncat /tmp/test_out.txt\nexit" | ./minishell
echo -e "cat < /etc/hostname\nexit" | ./minishell
echo -e "cat << EOF\nline1\nline2\nEOF\nexit" | ./minishell
rm -f /tmp/test_out.txt

# 17. Pipes
print_test "17. Pipes"
echo -e "echo hello | cat\nexit" | ./minishell
echo -e "ls | grep mini\nexit" | ./minishell
echo -e "cat /etc/hostname | cat | cat\nexit" | ./minishell
echo -e "ls filethatdoesntexist | grep bla\nexit" | ./minishell 2>&1 | head -5
echo -e "echo test > /tmp/test.txt\ncat /tmp/test.txt | grep test\nexit" | ./minishell
rm -f /tmp/test.txt

echo -e "\n${GREEN}==================================${NC}"
echo -e "${GREEN}Evaluation Tests Completed!${NC}"
echo -e "${GREEN}==================================${NC}"
