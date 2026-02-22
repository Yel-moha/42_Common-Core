#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
TEST_FILE="$ROOT/test_minishell_10_02_2025.txt"
TMP_DIR="$ROOT/.tmp_test_compare"
mkdir -p "$TMP_DIR"

SANITIZED_TEST="$TMP_DIR/test.sanitized"

MINI_RAW="$TMP_DIR/minishell.raw"
BASH_RAW="$TMP_DIR/bash.raw"
MINI_NORM="$TMP_DIR/minishell.norm"
BASH_NORM="$TMP_DIR/bash.norm"
DIFF_OUT="$TMP_DIR/diff.txt"

# Remove comments/headers and known non-test annotation lines.
# Keep heredoc content untouched (it doesn't use leading # in this file).
grep -Ev '^[[:space:]]*(#|\[)' "$TEST_FILE" > "$SANITIZED_TEST"

normalize_common() {
  sed -E 's/minishell\$ ?//g' \
    | grep -Fvxf "$SANITIZED_TEST" \
    | grep -Ev '^(SHLVL=|_=|declare -x SHLVL=|declare -x _=)' \
    | sed -E '/^\s*$/N;/^\n$/D'
}

# Run full scenario in minishell
./minishell < "$SANITIZED_TEST" > "$MINI_RAW" 2>&1 || true

# Run full scenario in bash
bash < "$SANITIZED_TEST" > "$BASH_RAW" 2>&1 || true

# Normalize common noisy lines (prompt and readline/control remnants)
cat "$MINI_RAW" | normalize_common > "$MINI_NORM"
cat "$BASH_RAW" | normalize_common > "$BASH_NORM"

# Compare
if diff -u "$BASH_NORM" "$MINI_NORM" > "$DIFF_OUT"; then
  echo "MATCH: minishell output matches bash for this test file"
else
  echo "DIFF: minishell output differs from bash"
  echo "---- Diff (first 200 lines) ----"
  head -n 200 "$DIFF_OUT"
fi

# Summary files
wc -l "$BASH_NORM" "$MINI_NORM"
