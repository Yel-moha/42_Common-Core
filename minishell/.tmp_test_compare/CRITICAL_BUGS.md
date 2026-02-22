# Critical Bugs Remaining (59 FAIL total)

## Exit Code Mismatches (Real Bugs)

### Case 070: echo with pipe and redirect
- **Line 97**: `echo "BIG BOY TEXT" | > out`
- **Expected**: bash=0 (creates file)
- **Got**: minishell=1 (parser error)
- **Issue**: Parser doesn't allow empty command after pipe with redirect

### Case 075: ls redirect with read from file
- **Line 106**: `ls > out | <out cat`
- **Expected**: bash=1 (file doesn't exist yet)
- **Got**: minishell=0 (no error on failed input redirect)
- **Issue**: Input redirect failure not propagating exit code

### Case 110: Quote concatenation edge case
- **Line 159**: `e'ch'"o " ciao`
- **Expected**: bash=127 (locale-specific behavior)
- **Got**: minishell=0 (quote concatenation works correctly)
- **Issue**: Possibly a bash locale issue, not a minishell bug

## Output Format Differences (Same Exit Code, Different Output)

### Case 004, 012: env/export output order
- Variables appear in different order than bash

### Case 019: echo with many spaces and special chars
- Whitespace handling in echo output

### Case 101, 102: Quote expansion edge cases
- Empty string concatenation: `ciao$""805409''` vs bash output

## Incomplete Cases (minishell=None, heredoc/syntax issues)

### Cases 124-147: Heredoc and syntax error handling
- Minishell stops responding after line 198 (heredoc pipe cases)
- Likely parser crash or infinite loop on complex heredoc+pipe+syntax combinations

---

## Priority for Fixing

1. **Case 070**: Parser should allow `| > file` pattern (create empty file)
2. **Case 075**: Input redirect failures should set exit code 1
3. **Cases 124+**: Debug why minishell stops on heredoc+pipe patterns
4. **Case 101/102**: Quote expansion (may be minor)
5. **Case 004/012**: Output order (cosmetic, doesn't affect functionality)
