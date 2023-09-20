#include "shell.h"

/**
 * _strtok - Splits a string into tokens based on delimiter characters.
 * @str: The string to be tokenized.
 * @delimiters: characters that determine where to split the string.
 * Return: A pointer to the next token, or NULL if there are no more tokens.
 */
char *_strtok(char *str, const char *delimiters)
{
	return (strtok(str, delimiters));
}

/**
 * _chrCheck - Checks if a character is present in a given string.
 * @c: The character to be checked.
 * @str: The string in which the character is to be searched.
 * Return: number of occurrences of character, or 0 if not found.
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
 * is_dir - Checks if the given path or name represents a directory.
 * @line: The input line or path to be checked.
 * @argv: Array of argument strings.
 * @counter: Counter representing the number of arguments
 * @line_vector: Vector of lines or paths related to the input.
 * @status: Pointer to an integer representing the status
 * @old_line: Previous input line or path for reference.
 * Return: 1 if the given path or name is a directory, 0 otherwise.
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

