#include "shell.h"

/**
 * parse_line - Splits a line into arguments array (tokens)
 * @line: The line typed by the user to split
 * Description: transform a line in an array
 * of string usable by execve
 *
 * Return: Array of arguments
 */
char **parse_line(char *line)
{
	char **args = malloc(sizeof(char *) * MAX_ARGS); /* allocate for array "64" */
	char *token; /* pointer to recup each words */
	int i = 0;

	if (!args) /* error malloc case */
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\n"); /* cut line in token (words) by using space and \n */
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token; /* stock the word */
		token = strtok(NULL, " \t\n"); /* continue to cut the same line */
	}
	args[i] = NULL; /* execve need an array finish by null */

	return (args);
}

/**
 * free_args - Frees the array of arguments
 * @args: Array to free
 * important to avoid memory leak
 *
 */
void free_args(char **args)
{
	free(args);
}
