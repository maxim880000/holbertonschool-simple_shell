#include "shell.h"

/**
 * print_environment - Prints all environment variables
 */
void print_environment(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * is_builtin - Checks if a command is a built-in
 * @command: Command name
 * is_builtin - Checks if a command is a built-in
 * @command: The command to check
 *
 * Return: 1 if built-in, 0 otherwise
 */
int is_builtin(char *command)
{
	if (strcmp(command, "exit") == 0)
		return (1);
	if (strcmp(command, "env") == 0)
		return (1);

	return (0);
}

/**
 * execute_builtin - Executes a built-in command
 * @args: Array of arguments
 *
 * Return: 256 if exit, 1 if executed, 0 otherwise
 * Return: 1 to indicate shell should exit, 0 otherwise
 */
int execute_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		return (256);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_environment();
		return (1);
	}
		return (1);

	return (0);
}
