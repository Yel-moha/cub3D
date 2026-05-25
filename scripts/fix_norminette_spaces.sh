#!/usr/bin/env bash
set -euo pipefail

# Fix mixed space/tab errors reported by norminette
# 1. Remove any trailing spaces/tabs after backslash continuation
# 2. Ensure consistent indentation (tabs for leading indent only)

find src -type f \( -name "*.c" -o -name "*.h" \) ! -path "*/minilibx-linux/*" | while read -r file; do
    # Remove spaces/tabs AFTER backslash (before newline)
    perl -i -pe 's/\\ +\\t*$/\\/g' "$file"
    perl -i -pe 's/\\	+$//g; s/\\ +$/\\/g' "$file"
done

exit 0
