#include "shell.h"

/**
 * print_command_error - Prints a command not found error
 * @shell_name: Shell name
 * @cmd_count: Command counter
 * @cmd: Command name
 */
void print_command_error(char *shell_name, int cmd_count, char *cmd)
 * execute_command - Executes a command with arguments and PATH support
 * @line: The command line to execute
 * @shell_name: Name of the shell program
 *
 * Return: 1 if shell should exit, 0 otherwise
 */
int execute_command(char *line, char *shell_name)
{
	fprintf(stderr, "%s: %d: %s: not found\n", shell_name, cmd_count, cmd);
}

/**
 * execute_child_process - Executes the command in the child process
 * @command_path: Command path
 * @args: Array of arguments
 * @shell_name: Shell name
 * @cmd_count: Command counter
 */
void execute_child_process(char *command_path, char **args,
		char *shell_name, int cmd_count)
{
	if (execve(command_path, args, environ) == -1)
	{
		print_command_error(shell_name, cmd_count, args[0]);
		free(command_path);
		exit(127);
		free_args(args);
		return (0);
	}

	if (is_builtin(args[0]))
	{
		status = execute_builtin(args);
		free_args(args);
		return (status);
	}
}

/**
 * fork_and_execute - Forks and executes the command
 * @command_path: Command path
 * @args: Array of arguments
 * @shell_name: Shell name
 * @cmd_count: Command counter
 *
 * Return: Exit status of the child process
 */
int fork_and_execute(char *command_path, char **args,
		char *shell_name, int cmd_count)
{
	pid_t pid;
	int status;
	command_path = find_in_path(args[0]);

	if (command_path == NULL)
	{
		fprintf(stderr, "%s: No such file or directory\n", shell_name);
		free_args(args);
		return (0);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(command_path);
		return (1);
	}
	else if (pid == 0)
	{
		execute_child_process(command_path, args, shell_name, cmd_count);
	}
	else
	{
		wait(&status);
		free(command_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

/**
 * execute_command - Executes a command
 * @args: Array of arguments
 * @shell_name: Shell name (argv[0])
 * @cmd_count: Pointer to the command counter
 *
 * Return: Exit status of the command
 */
int execute_command(char **args, char *shell_name, int *cmd_count)
{
	char *command_path;
	int status;

	if (args[0] == NULL)
		return (0);

	if (is_builtin(args[0]))
	{
		status = execute_builtin(args);
		if (status == 256)
			return (256);
		return (0);
	}

	command_path = find_in_path(args[0]);

	if (command_path == NULL)
	{
		print_command_error(shell_name, *cmd_count, args[0]);
		(*cmd_count)++;
		return (127);
	}

	status = fork_and_execute(command_path, args, shell_name, *cmd_count);
	(*cmd_count)++;
	return (status);

	return (0);
}
