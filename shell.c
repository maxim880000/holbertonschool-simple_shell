#include "shell.h"

/**
 * execute_command - Executes a command with arguments and PATH support
 * @line: The command line to execute
 * @shell_name: Name of the shell program
 */
void execute_command(char *line, char *shell_name)
{
	pid_t pid;
	int status;
	char **args;
	char *command_path;

	args = parse_line(line);

	if (args[0] == NULL)
	{
		free_args(args);
		return;
	}

	command_path = find_in_path(args[0]);

	if (command_path == NULL)
	{
		fprintf(stderr, "%s: No such file or directory\n", shell_name);
		free_args(args);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(command_path);
		free_args(args);
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		execve(command_path, args, environ);
		perror(shell_name);
		free(command_path);
		free_args(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		free(command_path);
		free_args(args);
	}
}

