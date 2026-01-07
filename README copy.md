# Simple Shell 0.1

## Description
This is a very basic UNIX command line interpreter that only executes commands with their full path.

## Features
- Displays a prompt `#cisfun$` and waits for user input
- Executes commands given with their full path (e.g., `/bin/ls`)
- Handles end-of-file condition (Ctrl+D)
- Displays error messages for invalid commands

## Limitations (as per task requirements)
- No PATH support (must use full path like `/bin/ls`)
- No built-in commands (exit, env, etc.)
- No arguments support (only single command names)
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
#cisfun$ /bin/ls
main.c  shell  shell.c  shell.h
#cisfun$ ls
./shell: No such file or directory
#cisfun$ exit
./shell: No such file or directory
#cisfun$ (Ctrl+D to exit)
```

### Non-interactive mode
```bash
$ echo "/bin/ls" | ./shell
main.c  shell  shell.c  shell.h
```

## Files
- `main.c` - Main entry point with prompt and getline loop
- `shell.c` - Command execution using fork and execve
- `shell.h` - Header file with function prototypes

## Author
Holberton School Project

