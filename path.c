#include "shell.h"

/**
 * _getenv - Gets an environment variable value
 * @name: Name of the environment variable
 *
 * Return: Value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t name_len;

	if (!name || !environ)
		return (NULL);

	name_len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, name_len) == 0 &&
		    environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
		i++;
	}

	return (NULL);
}

/**
 * check_absolute_path - Checks if it's an absolute/relative path
 * @command: Command name
 *
 * Return: Duplicated path if valid, NULL otherwise
 */
char *check_absolute_path(char *command)
{
	char *dup;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
		{
			dup = malloc(strlen(command) + 1);
			if (!dup)
				return (NULL);
			strcpy(dup, command);
			return (dup);
		}
		return (NULL);
	}
	return (NULL);
}

/**
 * build_full_path - Builds the full path
 * @dir: Directory
 * @command: Command name
 *
 * Return: Allocated full path or NULL
 */
char *build_full_path(char *dir, char *command)
{
	char *fullpath;
	int len;

	len = strlen(dir) + strlen(command) + 2;
	fullpath = malloc(len);
	if (!fullpath)
		return (NULL);

	sprintf(fullpath, "%s/%s", dir, command);
	return (fullpath);
}

/**
 * search_in_directories - Searches for the command in directories
 * @path_copy: Copy of PATH
 * @command: Command name
 *
 * Return: Full path or NULL
 */
char *search_in_directories(char *path_copy, char *command)
{
	char *dir, *fullpath;

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		fullpath = build_full_path(dir, command);
		if (!fullpath)
		{
			free(path_copy);
			return (NULL);
		}

		if (access(fullpath, X_OK) == 0)
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
 * find_in_path - Searches for a command in PATH
 * @command: Command name
 *
 * Return: Full path of the command or NULL if not found
 */
char *find_in_path(char *command)
{
	char *path, *path_copy, *result;

	result = check_absolute_path(command);
	if (result != NULL)
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
