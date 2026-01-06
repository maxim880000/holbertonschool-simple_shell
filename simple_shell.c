#include "shell.h"

/**
 * trim_line - Removes leading and trailing whitespace
 * @line: Line to trim
 *
 * Return: Pointer to trimmed string
 */
char *trim_line(char *line)
{
	char *end;

	while (*line == ' ' || *line == '\t' || *line == '\n')
		line++;

	if (*line == '\0')
		return (line);

	end = line + strlen(line) - 1;
	while (end > line && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	*(end + 1) = '\0';

	return (line);
}

/**
 * execute_command - Executes a command
 * @line: Command line to execute
 * @shell_name: Shell name (argv[0])
 *
 * Return: Exit status of the command
 */
int execute_command(char *line, char *shell_name)
{
	pid_t pid;
	int status;
	char *argv[2];
	static int cmd_count = 1;

	if (line[0] == '\0')
		return (0);

	argv[0] = line;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (1);
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
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

