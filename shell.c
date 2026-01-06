#include "shell.h"

/**
 * execute_command - Executes a command
 * @line: Command line to execute
 * @shell_name: Shell name (argv[0])
 */
void execute_command(char *line, char *shell_name)
{
	pid_t pid;
	int status;
	char *argv[2];
	static int cmd_count = 1;

	if (line[0] == '\0')
		return;

	argv[0] = line;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		if (execve(line, argv, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
					shell_name, cmd_count, line);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}

	cmd_count++;
}

