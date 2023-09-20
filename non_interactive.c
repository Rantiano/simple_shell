#include "shell.h"

/**
 * get_commands - Function obtains commands based on the specified mode.
 * @mode: The mode of operation as in (interactive, piped, or file-based).
 * @file_name: The name of the input file (used in NON_INTERACTIVE_FILE mode).
 * @program_name: This is the name of the shell program.
 *
 * Return: An array of strings obtained based on the specified mode, or NULL
 *         if an error occurs or if the specified mode is not recognized.
 */
char **get_commands(int mode, char *file_name, char *program_name)
{
	char **lines = NULL;

	if (mode == NON_INTERACTIVE_PIPED)
	{
		lines = piped_non_interactive();
		if (!lines)
			exit(0);
	}
	else if (mode == NON_INTERACTIVE_FILE)
	{
		lines = file_non_interactive(file_name, program_name);
		if (!lines)
			exit(0);
	}
	return (lines);
}


/**
 * piped_non_interactive - Reads and processes piped non-interactive input.
 *
 * Return: An array of strings representing individual commands obtained from
 *         the piped non-interactive input, or NULL if the input does not
 *         contain valid commands or if there is an error during processing.
 */
char **piped_non_interactive()
{
	char b[2048], *text = NULL, **lines = NULL;
	ssize_t bytesRead;
	size_t totalchar = 0;
	int i, flag = 0;

	while ((bytesRead = read(STDIN_FILENO, b, 2048)) > 0)
	{
		totalchar += bytesRead;
	}
	if (bytesRead == -1)
	{
		perror("read");
		exit(ERROR);
	}
	if (totalchar > 2048)
	{
		b[2048 - 1] = '\0';
	}
	else
	{
		b[totalchar - 1] = '\0';
	}

	for (i = 0; b[i]; i++)
	{
		if (b[i] != ' ' && b[i] != '\n' && b[i] != '\t'
						&& b[i] != '\r' && b[i] != '\a')
			flag = 1;
	}
	if (flag == 0)
		return (NULL);
	totalchar = _strlen(b);
	text = (char *)malloc((totalchar + 1) * sizeof(char));
	if (text != NULL)
	{
		_strcpy(text, b);
		text[totalchar] = '\0';
		lines = text_to_vector(text);
	}
	return (lines);
}

/**
 * text_to_vector - Function converts a text into an array of strings.
 * @text: Defines the input text to be split into multiple strings.
 *
 * Return: The last element of the array is NULL. If there are no newline
 *         characters in the input text or if there is an allocation error.
 */
char **text_to_vector(char *text)
{
	char *token, *cmd;
	char **lines = NULL;
	int i = 0;
	unsigned int c_count = 0;

	c_count = char_count_piped(text, '\n');
	lines = (char **)malloc((c_count + 1) * sizeof(char *));
	token = _strtok(text, "\n");
	cmd = _strdup(token);
	lines[i++] = cmd;
	while (token != NULL)
	{
		token = _strtok(NULL, "\n");
		if (token != NULL)
		{
			cmd = _strdup(token);
			lines[i++] = cmd;
		}
	}
	free(text);
	lines[i] = NULL;
	return (lines);
}

/**
 * file_non_interactive - Reads and processes non-interactive input of a file.
 * @file_name: The name of the input file that is to be processed.
 * @program_name: The name of the shell program.
 *
 * Return: An array of strings representing individual commands obtained from
 *         the non-interactive input file, or NULL if the file doesn't exist,
 *         or if there are file operations issues or memory allocation.
 */
char **file_non_interactive(char *file_name, char *program_name)
{
	struct stat fileStat;
	char *text, **lines;
	int file_descriptor;
	size_t letters;

	if (stat(file_name, &fileStat) != -1)
	{
		if (S_ISREG(fileStat.st_mode))
		{
			file_descriptor = open(file_name, O_RDONLY);
			if (file_descriptor  == -1)
				exit(ERROR);
			if (fileStat.st_size == 0)
				exit(0);
			text = malloc((fileStat.st_size + 1) * sizeof(char));
			if (!text)
				return (NULL);
			letters = read(file_descriptor, text, fileStat.st_size);
			if ((int) letters == -1)
			{
				perror("read");
			}
			close(file_descriptor);

			text[letters - 1] = '\0';
			if (text)
				lines = text_to_vector(text);
			return (lines);
		}
		else
			exit(0);
	}
	else
	{
		print_cant_open(program_name, 0, file_name);
		exit(127);
	}
	return (NULL);
}

