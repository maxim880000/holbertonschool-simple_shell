#include "shell.h"

/**
 * _getenv - Gets an environment variable
 * @name: Name of the variable
 *
 * Return: Pointer to the value, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t name_len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, name_len) == 0 &&
		    environ[i][name_len] == '=')
			return (environ[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

/**
 * check_absolute_path - Checks if command is an absolute path
 * @command: Command to check
 *
 * Return: Duplicated command if valid, NULL otherwise
 */
char *check_absolute_path(char *command)
{
	struct stat st;
	char *dup;

	if (command[0] == '/')
	{
		if (stat(command, &st) == 0)
		{
			dup = malloc(strlen(command) + 1);
			if (!dup)
				return (NULL);
			strcpy(dup, command);
			return (dup);
		}
	}
	return (NULL);
}

/**
 * build_full_path - Builds full path from directory and command
 * @dir: Directory path
 * @command: Command name
 *
 * Return: Full path string
 */
char *build_full_path(char *dir, char *command)
{
	char *fullpath;
	size_t len = strlen(dir) + strlen(command) + 2;

	fullpath = malloc(len);
	if (!fullpath)
		return (NULL);

	strcpy(fullpath, dir);
	strcat(fullpath, "/");
	strcat(fullpath, command);

	return (fullpath);
}

/**
 * search_in_directories - Searches for command in PATH directories
 * @path_copy: Copy of PATH variable
 * @command: Command to find
 *
 * Return: Full path if found, NULL otherwise
 */
char *search_in_directories(char *path_copy, char *command)
{
	char *dir, *fullpath;
	struct stat st;

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		fullpath = build_full_path(dir, command);
		if (!fullpath)
		{
			free(path_copy);
			return (NULL);
		}

		if (stat(fullpath, &st) == 0)
		{
			free(path_copy);
			return (fullpath);
		}

		free(fullpath);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * find_in_path - Finds the full path of a command
 * @command: Command to find
 *
 * Return: Full path if found, NULL otherwise
 */
char *find_in_path(char *command)
{
	char *path, *path_copy, *result;

	result = check_absolute_path(command);
	if (result)
		return (result);

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = malloc(strlen(path) + 1);
	if (!path_copy)
		return (NULL);
	strcpy(path_copy, path);

	return (search_in_directories(path_copy, command));
}

