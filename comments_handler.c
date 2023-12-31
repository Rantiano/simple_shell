#include "shell.h"

/**
 * handle_comments - Handles removal of comments from a line of text.
 * @line: A pointer to a null-terminated string containing the line of text.
 *
 * Return: void
 */
void handle_comments(char *line)
{
	int len = _strlen(line);
	int x = 0;
	int _strating = 0;

	for (x = 0; x < len; x++)
	{
		if (line[x] == ' ')
		{
			_strating = 0;
		}
		else if (line[x] == '#')
		{
			if (!_strating)
			{
				line[x] = '\0';
				break;
			}
		}
		/*
		 * this else handles the mid
		 */
		else
		{
			_strating = 1;
		}
	}
}

/**
 * _cd - Changes the current working directory.
 * @line_vector: An array of strings containing the command and its arguments.
 * @argv: The array of strings containing the command-line arguments.
 *
 * Return: 0 if the directory change is successful, 1 otherwise.
 */
int _cd(char **line_vector, char **argv)
{
	char *dir = line_vector[1];
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	if (dir == NULL || _strcmp(dir, "~") == 0)
		dir = _getenv("HOME");
	else if (_strcmp(dir, "-") == 0)
		dir = _getenv("OLDPWD");
	if (chdir(dir) == -1)
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": 1", 3);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, line_vector[0], _strlen(line_vector[0]));
		write(STDERR_FILENO, ": can't cd to ", 14);
		write(STDERR_FILENO, line_vector[1], _strlen(line_vector[1]));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	else
	{
		setenv("OLDPWD", cwd, 1);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd() error");
			return (1);
		}
	}
	return (0);
}

/**
 * free_all - Frees the allocated memory and the resources used by the shell.
 * @lines: An array of strings with user input lines.
 * @counter: An integer that represents the number of user input lines.
 * @env: A linked list of environ variables.
 * @current: A linked list that represents the current working directory.
 * @line: A pointer to a string that contains the last user input line.
 * @line_vector: An array of strings that contains the tokenized user input.
 *
 * Return: void
 */
void free_all(char **lines, int counter, list_path *env,
		list_path *current, char *line, char **line_vector)
{
	if (lines)
	{
		free(lines[counter]);
		if (lines)
			free(lines);
	}
	free_list(env);
	free_list(current);
	free_l_v(line, line_vector);
}
