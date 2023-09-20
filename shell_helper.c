#include "shell.h"

/**
 * check_mode - Checks mode of operation based on the number of arguments.
 * @argc: Count of arguments provided to the program
 * Return: integer representing the mode of operation.
 */
int check_mode(int argc)
{
	struct stat stdin_stat;

	fstat(STDIN_FILENO, &stdin_stat);
	if (isatty(STDIN_FILENO) && argc == 1)
		return (INTERACTIVE);
	if ((!isatty(STDIN_FILENO) && argc == 1))
		return (NON_INTERACTIVE_PIPED);
	if ((argc >= 1))
		return (NON_INTERACTIVE_FILE);

	return (ERROR);
}

/**
 * is_exit - Checks if the given input is an "exit" command
 * @line: The input line or command to be checked.
 * @line_vector: Vector of lines or commands
 * @current: Pointer to the current path
 * @program_name: Name of the program being executed.
 * @counter: Counter representing the number of commands performed.
 * @status: Pointer to an integer representing the status
 * @env: Pointer to the environment variables or settings.
 * @lines: Array of previous input lines or commands
 */

void is_exit(char *line, char **line_vector, list_path *current,
		char *program_name, int counter, int *status, list_path *env, char **lines)
{
	int n;

	if (_strcmp(line_vector[0], "exit") == 0)
	{
		if (line_vector[1] == NULL)
		{
			free_all(lines, counter, env, current, line, line_vector);
			exit(*status);
		}
		else if (line_vector[1] != NULL)
		{
			if (_strlen(line_vector[1]) <= 9)
			{
				n = _atoi(line_vector[1]);
				if (n != -1)
				{
					free_all(lines, counter, env, current, line, line_vector);
					exit(n);
				}
				else
				{
					*status = EXIT_ERROR;
					print_error(program_name, counter, line_vector[1], EXIT_ERROR);
				}
			}
			else
			{
				*status = EXIT_ERROR;
				print_error(program_name, counter, line_vector[1], EXIT_ERROR);
			}
		}
	}
}

/**
 * _atoi - Converts a string to an integer.
 * @s: Pointer to the string to be converted.
 * Return: The integer representation of the string.
 */
int _atoi(char *s)
{
	unsigned int n, i;
	char positive;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (!((s[i] >= '0') && (s[i] <= '9')))
		{
			return (-1);
		}
		if (((s[i] >= '0') && (s[i] <= '9')))
		{
			n = (n * 10) + (s[i] - '0');
		}
		else if (s[i] == '+')
			positive++;

		i++;
	}

	return (n);
}

/**
 * execute_command - Executes a command using the given path,
 * @path: Path to the command or executable to be run.
 * @av: Array of arguments to be passed to the command.
 * @env: Array of environment variables to be set for the command.
 * @status: Pointer to an integer representing the status
 */

void execute_command(char *path, char **av, char **env, int *status)
{
	pid_t pid;

	pid = fork();
	if (pid == ERROR)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(path, av, env) == -1)
			exit(126);
	}
	else if (pid > 0)
	{

		waitpid(pid, status, WUNTRACED);
		*status  = WEXITSTATUS(*status);
	}
}

/**
 * free_vector - Frees the memory allocated for a vector
 * @argv: Pointer to the array of strings to be freed.
 */
void free_vector(char **argv)
{
	char **curr;

	if (argv == NULL)
		return;

	curr = argv;
	while (*curr != NULL)
	{
		free(*curr);
		curr++;
	}

	free(argv);
}

