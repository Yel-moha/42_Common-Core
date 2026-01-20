#!/bin/bash

# Minimal valgrind regression suite for minishell.
# Uses vgmini if available, otherwise falls back to valgrind with a strict config.

set -euo pipefail

choose_runner() {
    if command -v vgmini >/dev/null 2>&1; then
        echo "vgmini"
    elif command -v valgrind >/dev/null 2>&1; then
        echo "valgrind --leak-check=full --error-exitcode=42 --quiet --suppressions=minishell.supp"
    else
        echo "No valgrind runner found (vgmini or valgrind)." >&2
        exit 1
    fi
}

VG_RUNNER=${VG_RUNNER:-$(choose_runner)}
MINISHELL=${MINISHELL:-./minishell}

# name | payload (ANSI-C quoted; no variable expansion)
TESTS=(
    "cmd_missing|$'zzz\n'"
    "exit_only|$'exit\n'"
    "ctrl_d_empty|$''"  # run interactively if desired
    "double_pipe|$'cat | | ls\n'"
    "pipe_end|$'echo hi |\n'"
    "pipe_start|$'| echo hi\n'"
    "pipe_only|$'|\n'"
    "redir_in_missing|$'<\n'"
    "redir_out_missing|$'echo hi >\n'"
    "heredoc_empty|$'cat <<EOF\n'"  # no terminator provided
    "heredoc_expand|$'cat <<EOF\n$PATH\nEOF\n'"
    "heredoc_no_expand|$'cat <<"EOF"\n$PATH\nEOF\n'"
    "unset_missing|$'unset XYZ\n'"
    "cd_fail|$'cd /non/esiste\n'"
    "run_nonexec|$'./Makefile\n'"
)

run_test() {
    local name="$1" payload="$2" log status summary
    log=$(mktemp)
    printf "\n[TEST] %s\n" "$name"
    # Send payload to minishell via stdin.
    printf "%s" "$payload" | eval "$VG_RUNNER" "$MINISHELL" >"$log" 2>&1 || true
    status=$?
    summary=$(grep -E "(definitely|indirectly|possibly|still reachable):" "$log" 2>/dev/null | tail -4 || true)
    errors=$(grep -E "ERROR SUMMARY" "$log" 2>/dev/null | tail -1 || true)
    printf "status=%d\n" "$status"
    printf "%s\n" "$summary"
    printf "%s\n" "$errors"
    # Uncomment to see full output
    # cat "$log"
    rm -f "$log"
}

main() {
    printf "Using runner: %s\n" "$VG_RUNNER"
    printf "Minishell:   %s\n" "$MINISHELL"
    for entry in "${TESTS[@]}"; do
        IFS='|' read -r name payload <<<"$entry"
        run_test "$name" "$payload"
    done
}

main "$@"
