#include "shell.h"

/**
 * handle_exit - Handles the exit built-in
 * @args: Array of arguments
 * @line: Line typed by user read by getline
 * @exit_status: Exit status to return
 */
void handle_exit(char **args, char *line, int exit_status)
{
	free_args(args);
	free(line);
	exit(exit_status); /* quit the program with the code exit_status */
}

/**
 * main - Entry point of the simple shell
 * @argc: Number of arguments
 * @argv: Array of arguments 
 *
 * Return: Exit status of last command
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0; /* unsigned + */
	ssize_t nread; /* nb of char read */
	int interactive, cmd_count = 1, exit_status = 0, last_status = 0;
	char **args; /* array to stock arguments */

	(void)argc;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
		{
			printf("($) ");
			fflush(stdout); /* force immediate display */
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
	}
	free(line);
	return (exit_status);
}
