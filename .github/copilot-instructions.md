Project: Minishell-Master — Copilot guidance

Overview
- This repository implements a small POSIX-like shell (minishell) in C. Key components live in `src/` and public types/headers in `inc/`.
- Global program state is carried in `t_big` (`inc/minishell.h`) and passed to most subsystems.

Where to look first
- `src/main.c`: program entry, initialization and main loop.
- `inc/minishell.h`: central runtime types (`t_big`, `t_env`) and the `g_signal` global.
- `inc/parser.h`: token/parse/command data structures (`t_token`, `t_parse`, `t_cmd`, `t_redir`) and parsing APIs.
- `src/parsing/`: tokenization, expansion and parser flow. See `expand.c` / `expand_word` for dollar/quote handling.
- `src/execution/`: command execution and fork/pipe coordination.
- `src/builtins/`: builtin implementations (cd, echo, env, export, unset, exit, pwd, execve helpers).
- `src/utils/`: helpers including `heredoc.c` and file I/O utilities.
- `lib/libft/`: included utility library — built by its own Makefile; artifacts are expected at `lib/libft/bin/libft.a`.

Build / run / debug
- Build: run `make` in the repository root. This builds `lib/libft` then compiles the minishell binary `minishell`.
- Clean: `make clean` / `make fclean` / `make re`.
- Run: `./minishell` from the repo root after `make`.
- Memory checks: use Valgrind manually, example:
  `valgrind --suppressions=./readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./minishell`
- Debugging with gdb: `gdb --args ./minishell` then `run`.

Project-specific conventions & patterns
- Single global state object: most functions accept a `t_big *v` parameter and mutate or read runtime state there. Prefer passing it rather than using more globals.
- Linked lists: tokens (`t_token`) and commands (`t_cmd`) are linked lists. Free helpers exist (e.g. `free_parsed`, `freecmd_list`). Check `inc/parser.h` for API functions like `new_token`, `add_token`, `parse_cmd`.
- Expansion and quotes: Expansion is controlled by `expand_word` in `src/parsing/expand.c`. It tracks `in_q`/`in_dq` and calls `process_dollar` / `rem_dollar`. Note: expansion may return NULL on error — callers assign the returned pointer back to the token's `content`.
- Heredoc handling: heredocs are created by code in `src/utils/heredoc.c` and indicated by token type `T_HEREDOC`. Parsing sets `v->check_hdoc` around heredoc tokens to suppress normal expansions when appropriate (see `expand_tokens` in `src/parsing/expand.c`).
- Redirection metadata: `t_redir` has flags `expand` and `hdoc_created` which control whether filenames are expanded and whether the heredoc file was created.
- Libft usage: utility helpers and string routines are in `lib/libft/src`. When changing libft, run its Makefile in `lib/libft/` — `make` at repo root will build libft automatically.

Reliable search shortcuts
- To find parsing logic: search `src/parsing/**` or `handle_word`, `make_tokens`, `process_dollar` in `inc/parser.h`.
- To find execution flow: search `src/execution/exec.c`, `exec_fork.c` and `cmd_selectors.c`.
- To inspect builtins: `src/builtins/*.c`.

Editing notes & pitfalls
- When editing parser/expansion code, remember tokens are mutable C strings; `expand_word` may reallocate and return a new pointer — always assign its return value and check for NULL.
- Signal handling: `g_signal` exists for signal state; be careful changing signal setup in `main.c` or utilities as it affects child/fork behavior.
- Makefile details: object and dependency files are emitted to `obj/` and `dep/` respectively. The Makefile compiles with `-g -MMD -MP` so small source edits will create `.d` files in `dep/`.
- Keep `readline.supp` when running Valgrind to suppress spurious leaks from the readline library.

When in doubt (typical tasks)
- Add a new command/builtin: add files to `src/builtins/`, update `SRC` in the `Makefile` and implement the API expected by `main`/execution.
- Add parser behavior: update `src/parsing/*` and `inc/parser.h` prototypes; maintain token types in the `t_token_type` enum.
- Fix memory leaks: run Valgrind with `readline.supp` and follow the program flow from `main.c` through parsing -> execution -> cleanup.

Examples (concrete references)
- `inc/parser.h` defines `t_token`, `t_parse`, `t_cmd` and functions like `parse`, `make_tokens`, `expand_tokens`.
- `src/parsing/expand.c` shows how `v->check_hdoc` is used to avoid expanding heredoc contents and how `expand_word` toggles `in_q`/`in_dq`.
- `src/utils/heredoc.c` contains the heredoc create/read flow—changes here affect how `T_HEREDOC` tokens are handled by the parser and the expansion step.

If anything here is unclear or you want this guidance expanded (more examples, checklist for PRs, or rules for using `libft`), tell me which area to expand and I will iterate.
