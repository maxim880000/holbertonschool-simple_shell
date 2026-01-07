#include "shell.h"

/**
 * main - Simple shell 0.4 - with exit built-in
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO);
	int should_exit;

	(void)argc;

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
	return (0);
}
