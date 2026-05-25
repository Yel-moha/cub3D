#!/usr/bin/env bash
set -euo pipefail

# Replace leading groups of 4 spaces with tabs and remove trailing whitespace
# Operates in-place on files under src/ and preserves timestamps via temporary file

find src -type f -name "*.c" -o -name "*.h" | while read -r file; do
    # Convert leading groups of 4 spaces into tabs (preserve multiples)
    perl -0777 -pe 's{^((?: {4})+)}{"\t" x (length($1)/4)}mge' "$file" > "$file.tmp"
    # Remove trailing spaces and tabs
    sed -E 's/[ \t]+$//' "$file.tmp" > "$file.clean"
    mv "$file.clean" "$file"
    rm -f "$file.tmp"
done

# Exit successfully
exit 0
