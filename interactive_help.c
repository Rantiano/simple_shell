#include "shell.h"

/**
 * get_command_from_user - .
 * @current: .
 * Return: .
 */
char *get_command_from_user(list_path *current)
{
	ssize_t nread;
	size_t n = 0;
	char *line = NULL;

	write(STDOUT_FILENO, "^_* -> ", 7);
	nread = _getline(&line, &n, stdin);
	if (nread == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(line);
		free_list(current);
		exit(0);
	}

	if (line[0] == '\n' && nread == 1)
	{
		free(line);
		return (NULL);
	}
	line[nread - 1] = '\0';

	return (line);
}
/**
 * get_command_from_file - .
 * @file: .
 * Return: .
 */

char *get_command_from_file(char *file)
{
	return (file);
}

