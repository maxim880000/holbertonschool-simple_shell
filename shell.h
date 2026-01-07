#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

extern char **environ;

/* Parsing */
char **parse_line(char *line);
void free_args(char **args);

/* Execution */
int execute_command(char **args, char *shell_name, int *cmd_count);

/* PATH */
char *_getenv(const char *name);
char *find_in_path(char *command);

/* Built-ins */
int is_builtin(char *command);
int execute_builtin(char **args);
void print_environment(void);

#endif
