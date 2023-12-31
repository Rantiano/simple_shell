#include "shell.h"

/**
 * get_command_from_user - Function reads a command line input from the user.
 * @current: This is a pointer to the current working directory.
 *
 * Return: A pointer to the dynamically allocated input line by the user,
 *         or NULL if the user enters an empty line,
 *         or if an EOF condition is encountered.
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
 * get_command_from_file - This function reads a command from a file.
 * @file: The name of the file from which the command is to be read.
 *
 * Return: A pointer to the file name.
 */

char *get_command_from_file(char *file)
{
	return (file);
}

