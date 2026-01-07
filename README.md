# Simple Shell 0.3

## Description
This is a UNIX command line interpreter with PATH support that can execute commands with or without full paths.

## Features
- Displays a prompt `:) ` and waits for user input
- Executes commands with their full path (e.g., `/bin/ls -l`)
- **NEW: Supports PATH** - can find commands without full path (e.g., `ls`)
- **NEW: No fork if command doesn't exist** - validates before forking
- Supports command arguments (e.g., `ls -l -a`)
- Handles end-of-file condition (Ctrl+D)
- Displays error messages for invalid commands

## Limitations (as per task requirements)
- No built-in commands (exit, env, etc.)
- No special characters handling
- No pipes, redirections, or semicolons

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
```

## Usage

### Interactive mode
```bash
$ ./shell
:) ls
main.c  shell  shell.c  shell.h  path.c  helpers.c
:) /bin/ls -l
total 48
-rw-r--r-- 1 user user  1234 Jan  6 12:00 main.c
...
:) ls -l /tmp
total 20
drwx------ 3 root root 4096 Dec  5 12:09 systemd-private-...
...
:) pwd
/home/user/shell
:) (Ctrl+D to exit)
```

### Non-interactive mode
```bash
$ echo "ls" | ./shell
main.c  shell  shell.c  shell.h

$ echo "ls -l" | ./shell
total 48
-rw-r--r-- 1 user user 1234 Jan  6 12:00 main.c
...
```

## Files
- `main.c` - Main entry point with prompt and getline loop
- `shell.c` - Command execution using fork and execve
- `path.c` - PATH handling and command lookup
- `helpers.c` - Argument parsing with strtok
- `shell.h` - Header file with function prototypes

## Changes from v0.2
- Added PATH support via `_getenv` and `find_in_path`
- Commands are validated before forking (no fork if command doesn't exist)
- Prompt changed from `#cisfun$` to `:)`
- Example: `ls` now works (not just `/bin/ls`)

## Author
Holberton School Project

