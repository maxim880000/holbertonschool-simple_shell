#include "shell.h"

/**
 * main - Entry point of the simple shell
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive;
	char *trimmed;

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

		trimmed = trim_line(line);

		execute_command(trimmed, argv[0]);
	}

	free(line);
	return (0);
}
