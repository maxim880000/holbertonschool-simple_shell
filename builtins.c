#include "shell.h"

/**
 * is_builtin - Checks if a command is a built-in
 * @command: The command to check
 *
 * Return: 1 if built-in, 0 otherwise
 */
int is_builtin(char *command)
{
	if (strcmp(command, "exit") == 0)
		return (1);

	return (0);
}

/**
 * execute_builtin - Executes a built-in command
 * @args: Array of arguments
 *
 * Return: 1 to indicate shell should exit, 0 otherwise
 */
int execute_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		return (1);

	return (0);
}
