#include "shell.h"

/**
 * _strtok - .
 * @str: .
 * @delimiters: .
 * Return: .
 */
char *_strtok(char *str, const char *delimiters)
{
	return (strtok(str, delimiters));
}

/**
 * _chrCheck - .
 * @c: .
 * @str: .
 * Return: .
 */
unsigned int _chrCheck(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * free_l_v - Entry point to the shell
 * @line: arguements count
 * @line_vector: arguements values
 */
void free_l_v(char *line, char **line_vector)
{
	free(line);
	free_vector(line_vector);
}

/**
 * is_dir - Entry point to the shell
 * @line: arguements count
 * @argv: arguements count
 * @counter: arguements count
 * @line_vector: arguements count
 * @status: arguements count
 * @old_line: arguements count
 * Return: is dir or not
 */
int is_dir(char *line, char **argv, int counter, char **line_vector,
		int *status, char *old_line)
{
	struct stat st;

	if (stat(line, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			print_error(argv[0], counter, line_vector[0], PERMISSION_DENIED);
			*status = PERMISSION_DENIED;
			free_l_v(old_line, line_vector);
			return (0);
		}
	}
	return (-1);
}

