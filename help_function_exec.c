#include "shell.h"

/**
 * get_av_with_flags_helper - func helps to process tokens in a command line.
 * @token: The token extracted from the command line.
 * @line: Represents the original command line.
 * @av: An array of strings to be used in storing processed tokens.
 * @status: Exiting status of the previous command.
 *
 * Return: Pointer to a dynamically allocated string (cmd) that contains the
 *         processed token, or NULL if there is an error.
*/

char *get_av_with_flags_helper(char *token, char *line, char **av, int status)
{
		char *var, *cmd, *line_cpy;

	line_cpy = line;
		if (token == NULL)
	{
		free(av);
		free(line_cpy);
		return (NULL);
	}
	if (_strcmp("$$", token) == 0)
		cmd = get_process_id();
	else if (_strcmp("$?", token) == 0)
		cmd = get_status(status);
	else if ((token[0] == '$') && (token[1]))
	{
		var = _getenv(&token[1]);
		if (var)
			cmd = _strdup(var);
		else
			cmd = _strdup("");
	}
	else
		cmd = _strdup(token);

	return (cmd);
}
/**
 * get_av_with_flags - This parses a command line into an array of strings.
 * @line: The input command line needed to be parsed.
 * @status: The exit status of the previous command line.
 *
 * Return: A pointer to a dynamically allocated array of strings of the parsed
 *         command line, or NULL if an error occur or the input line is empty.
 */
char **get_av_with_flags(char *line, int status)
{
	char *line_cpy, *token, **av, *var, *cmd;
	int i = 0, c_count;

	handle_comments(line);
	if (line[0] == '\0')
		return (NULL);
	line_cpy = _strdup(line);
	if (line_cpy == NULL)
		return (NULL); /*can't cpy*/
	c_count = char_count(line_cpy, ' ');
	av = malloc((c_count + 1) * sizeof(char *));
	token = _strtok(line_cpy, TOK_D);

	cmd = get_av_with_flags_helper(token, line, av, status);
	av[i++] = cmd;
	while (token != NULL)
	{
		token = _strtok(NULL, TOK_D);
		if (token != NULL)
		{
			if (_strcmp("$$", token) == 0)
				cmd = get_process_id();
			else if (_strcmp("$?", token) == 0)
				cmd = get_status(status);
			else if ((token[0] == '$') && (token[1]))
			{
				var = _getenv(&token[1]);
				if (var)
					cmd = _strdup(var);
				else
					cmd = _strdup("");
			}
			else
				cmd = _strdup(token);
			av[i++] = cmd;
		}
	}
	av[i] = NULL;
	free(line_cpy);
	return (av);
}

/**
 * exit_check - Checks if the user entered an exit command or End of File.
 * @nread: The return value of a read operation, typically used to detect EOF.
 * @exit_cmd: The command entered by user for checking an exit command.
 *
 * Return: void
 */
void exit_check(int nread, char *exit_cmd)
{
	if (nread == EOF)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (_strcmp(exit_cmd, "exit") == 0)
	{
		exit(0);
	}
	if (_strcmp(exit_cmd, "exit") == 0)
	{
		exit(0);
	}
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @name: The name of the environment variable to be retrieved.
 *
 * Return: A pointer to the value of the environment variable 'name', or NULL
 *         if the variable is not found or if 'name' is NULL.
 */

char *_getenv(char *name)
{
	int i = 0, j = 0;

	if (name == NULL)
		return (NULL);
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] != '=')
		{
			if (environ[i][j] != name[j])
				break;
			if (environ[i][j] == name[j] && (environ[i][j + 1] == '='))
				return (&environ[i][_strlen(name) + 1]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/**
 * char_count - Counts num of occurrences of a char followed by another char.
 * @str: A pointer to the null-terminated string to be searched within.
 * @c: The character to be counted within the string.
 *
 * Return: Num of occurrences of 'c' followed by another char in the string.
 */

unsigned int char_count(char *str, char c)
{
	unsigned int count = 0;

	while (*str != '\0')
	{
		if (*str != c && *(str + 1) == c)
			count++;
		str++;
	}
	return (count + 1);
}

