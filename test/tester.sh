#!/usr/bin/env bash

# Resolve paths relative to this script so it can be run from anywhere
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
PROJECT_ROOT=$(cd "$SCRIPT_DIR/.." && pwd)
MINISHELL="$PROJECT_ROOT/minishell"
TEST_DIR="$PROJECT_ROOT/test"
TESTS="$TEST_DIR/tests"
RESULTS_DIR="$TEST_DIR/results"
SUPP_FILE="$PROJECT_ROOT/readline.supp"

mkdir -p "$RESULTS_DIR"
touch "$TEST_DIR/no_permission"
chmod 000 "$TEST_DIR/no_permission"
TEST_FILES="$TEST_DIR/file1 $TEST_DIR/file2 $TEST_DIR/no_permission"

# Build the project before running tests
echo "Building project..."
if ! (cd "$PROJECT_ROOT" && make); then
    echo "Failed to build project (make). Aborting."
    exit 2
fi

# Check valgrind availability
if command -v valgrind >/dev/null 2>&1; then
    HAS_VALGRIND=1
else
    HAS_VALGRIND=0
    echo "Warning: valgrind not found, memory checks will be skipped."
fi

# --- Handle Ctrl+C cleanly ---
cleanup() {
    echo ""
    echo "Interrupted. Cleaning up..."
    rm -f "$TEST_DIR"/test_block_*.sh $TEST_FILES
    exit 1
}
trap cleanup INT

# --- Split tests into numbered blocks ---
awk '
  BEGIN { i = 0 }
  /^###/ { i++; x = sprintf("'"$TEST_DIR"'/test_block_%03d.sh", i); next }
  # Skip comment-only lines and empty lines
  /^[[:space:]]*#/ { next }
  /^[[:space:]]*$/ { next }
  { print > x }
' "$TESTS"

i=1
success=0
total=0

for f in "$TEST_DIR"/test_block_*.sh; do
    total=$((total + 1))
    id=$(printf "%03d" $i)
    test_dir="$RESULTS_DIR/$id"
    mkdir -p "$test_dir"

    # --- Save the test file ---
    cp "$f" "$test_dir/command.txt"

    # --- Construct the command line for display ---
    cmd=""
    in_here=0
    delim=""
    while IFS= read -r line || [ -n "$line" ]; do
        # Skip commented lines
        [[ "$line" =~ ^# ]] && continue

        if [[ $in_here -eq 0 ]]; then
            if echo "$line" | grep -q '<<'; then
                delim=$(echo "$line" | awk -F'<<' '{gsub(/^[ \t]+|[ \t]+$/, "", $2); print $2}')
                in_here=1
                cmd+="$line // "
                continue
            fi
        else
            cmd+="$line // "
            [[ "$line" == "$delim" ]] && in_here=0
            continue
        fi

        # Normal line
        [[ -n "$line" ]] && cmd+="$line // "
    done < "$f"
    cmd="${cmd% // }"  # remove trailing " // "

    # --- Run in bash ---
    bash "$f" >"$test_dir/bash.out" 2>"$test_dir/bash.err"
    echo $? >"$test_dir/bash.status"

    # --- Run in minishell (under valgrind when available) ---
    VALGRIND_LOG="$test_dir/valgrind.log"
    if [ "$HAS_VALGRIND" -eq 1 ]; then
        timeout 7s valgrind --quiet \
            --suppressions="$SUPP_FILE" --leak-check=full --track-fds=yes \
            --show-leak-kinds=all --trace-children=yes \
            --log-file="$VALGRIND_LOG" \
            "$MINISHELL" <"$f" >"$test_dir/mini.out" 2>"$test_dir/mini.err"
        echo $? >"$test_dir/mini.status"
    else
        # run without valgrind
        timeout 7s "$MINISHELL" <"$f" >"$test_dir/mini.out" 2>"$test_dir/mini.err"
        echo $? >"$test_dir/mini.status"
        # ensure valgrind log exists but empty
        : >"$VALGRIND_LOG"
    fi

    bash_status=$(cat "$test_dir/bash.status")
    mini_status=$(cat "$test_dir/mini.status")

    # --- Normalize minishell stdout: remove ANSI color codes and prompt strings ---
    if [ -s "$test_dir/mini.out" ]; then
        # remove common ANSI color sequences like '\e[38;5;47m' and '\e[0m'
        # use $'...' to allow \x1B escape
        sed -i $'s/\x1B\[[0-9;]*m//g' "$test_dir/mini.out" 2>/dev/null || true
        # remove leftover prompt token `Minishell:> ` at start of lines
        sed -i -E 's/^Minishell:> //g' "$test_dir/mini.out" 2>/dev/null || true
        # remove lines that are empty after stripping prompt
        sed -i '/^[[:space:]]*$/d' "$test_dir/mini.out" 2>/dev/null || true
        # remove any lines that exactly match the original test commands (read from command.txt)
        if [ -f "$test_dir/command.txt" ]; then
            awk 'NR==FNR{a[$0];next} !($0 in a)' "$test_dir/command.txt" "$test_dir/mini.out" > "$test_dir/mini.out.clean" 2>/dev/null || true
            [ -f "$test_dir/mini.out.clean" ] && mv "$test_dir/mini.out.clean" "$test_dir/mini.out"
        fi
    fi

    stdout_diff=$(diff -q "$test_dir/bash.out" "$test_dir/mini.out")

	# Normalize Bash stderr in-place: remove "script_name: line N: " prefix
	sed -i -E 's|^[^:]+: line [0-9]+: ||' "$test_dir/bash.err"
	# Normalize minishell stderr in-place: remove "minishell: " prefix
	sed -i -E 's|^minishell: ||' "$test_dir/mini.err"
	stderr_diff=$(diff -q "$test_dir/bash.err" "$test_dir/mini.err")


    # --- Memory analysis ---
    valgrind_errors=0
    if [ "$HAS_VALGRIND" -eq 1 ]; then
        # Count summaries (always produce integers)
        total_summaries=$(grep -c "ERROR SUMMARY:" "$VALGRIND_LOG")
        clean_summaries=$(grep -c "ERROR SUMMARY: 0 errors" "$VALGRIND_LOG")

        # 1. Any non-clean summary = error
        if [ "$total_summaries" -gt 0 ] && [ "$total_summaries" -ne "$clean_summaries" ]; then
            valgrind_errors=1
        fi

        # 2. Any non-zero definitely lost = error
        if grep -Po "(?<=definitely lost: )\d+" "$VALGRIND_LOG" | grep -vq "^0$"; then
            valgrind_errors=1
        fi

        # 3. Timeout / crash = empty log = error
        if [ ! -s "$VALGRIND_LOG" ]; then
            valgrind_errors=1
        fi
    fi

    # --- Build warning reasons ---
    warn_reasons=()
    [[ -n "$stdout_diff" ]] && warn_reasons+=("stdout mismatch")
    [[ -n "$stderr_diff" ]] && warn_reasons+=("stderr mismatch")
    [[ "$bash_status" != "$mini_status" ]] && warn_reasons+=("exit status mismatch")
    [[ "$valgrind_errors" -eq 1 ]] && warn_reasons+=("memory errors")

    # --- Save diffs for inspection ---
    diff -u "$test_dir/bash.out" "$test_dir/mini.out" >"$test_dir/diff.stdout" || true
    diff -u "$test_dir/bash.err" "$test_dir/mini.err" >"$test_dir/diff.stderr" || true

    # --- Evaluate result ---
    # Special rule: green tick if only stderr differs
    only_stderr_warn=false
    if [[ ${#warn_reasons[@]} -eq 1 && "${warn_reasons[0]}" == "stderr mismatch" ]]; then
        only_stderr_warn=true
    fi

    if [[ ${#warn_reasons[@]} -eq 0 || $only_stderr_warn == true ]]; then
        printf "[%03d] ✅  %s\n" "$i" "$cmd"
        success=$((success + 1))
        [[ $only_stderr_warn == true ]] && echo "      stderr mismatch"
        [[ $valgrind_errors -eq 1 ]] && echo "      memory leaks"
    else
        printf "[%03d] ⚠️  %s\n" "$i" "$cmd"
        for reason in "${warn_reasons[@]}"; do
            echo "      $reason"
        done
    fi

    # --- Save summary for each test ---
    {
        echo "Test: $id"
        echo "Command: $cmd"
        echo "Bash exit: $bash_status"
        echo "Mini exit: $mini_status"
        [[ -n "$stdout_diff" ]] && echo "stdout differs"
        [[ -n "$stderr_diff" ]] && echo "stderr differs"
        [[ "$valgrind_errors" -eq 1 ]] && echo "memory leaks detected"
    } >"$test_dir/result.txt"

    i=$((i + 1))
done

# --- Summary ---
echo ""
echo "Summary: $success / $total tests passed ✅"

# --- Clean temporary test block files ---
rm -f $TEST_DIR/test_block_*.sh $TEST_FILES
