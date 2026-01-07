#include "shell.h"

/**
 * handle_exit - Handles the exit built-in
 * @args: Array of arguments
 * @line: Line buffer to free
 * @exit_status: Exit status to return
 */
void handle_exit(char **args, char *line, int exit_status)
{
	free_args(args);
	free(line);
	exit(exit_status);
}

/**
 * main - Entry point of the simple shell
 * @argc: Number of arguments
 * @argv: Array of arguments
 * main - Simple shell 0.4 - with exit built-in
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Exit status of last command
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive, cmd_count = 1, exit_status = 0, last_status = 0;
	char **args;
	int interactive = isatty(STDIN_FILENO);
	int should_exit;

	(void)argc;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
		{
			printf("($) ");
			fflush(stdout);
		}
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				printf("\n");
			break;
		}
		args = parse_line(line);
		exit_status = execute_command(args, argv[0], &cmd_count);
		if (exit_status == 256)
			handle_exit(args, line, last_status);
		if (exit_status != 256)
			last_status = exit_status;
		free_args(args);

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] != '\0')
		{
			should_exit = execute_command(line, argv[0]);
			if (should_exit)
				break;
		}
	}
	free(line);
	return (exit_status);
}
