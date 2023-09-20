#include "shell.h"

/**
 * print_env - This function prints the environ var to the standard output.
 * @status: A pointer to an int that stores the exit status of the function.
 *
 * Return: void
 */
void print_env(int *status)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	*status = 0; /*success*/
}

/**
 * get_status - Converts an int to a string representing the status.
 * @n: The int value to be converted to a string.
 *
 * Return: An allocated string representing the value of the status.
 */
char *get_status(int n)
{
	char *status;

	status = num_to_char(n);
	return (status);
}

/**
 * get_process_id - This gets the process ID (PID) of the current process.
 *
 * Return: An allocated string that represents the process ID (PID).
 */
char *get_process_id()
{
	char *ppid_s;
	pid_t pid = getpid();

	ppid_s = num_to_char(pid);

	return (ppid_s);
}

/**
 * is_built_in - Checks the built-in shell status of a command and executes.
 * @line: This is the original user input command.
 * @line_vector: An array containing the tokenized command.
 * @current: Pointer to the current working directory.
 * @program_name: The shell program name.
 * @counter: The current command counter.
 * @status: A pointer to an int that stores the exit status of the function.
 * @env_list: A linked list of the environment variables.
 * @lines: An array of lines containing inputs of the user.
 * @argv: An array of command-line arguments.
 *
 * Return: 0 if the command is a built-in and executed success, -1 otherwise.
 */
int is_built_in(char *line, char **line_vector, list_path *current,
	char *program_name, int counter, int *status, list_path *env_list,
	char **lines, char **argv)
{
	int i, n = -1;
	char *built_in[] = {"env", "exit", "cd", "setenv", "unsetenv"};

	for (i = 0; i < 5; i++)
	{
		if (_strcmp(built_in[i], line_vector[0]) == 0)
		{
			n = i;
			break;
		}
	}
	if (n == -1)
		return (n);

	switch (n)
	{
		case 0:
			print_env(status);
			break;
		case 1:
			is_exit(line, line_vector, current, program_name,
					counter, status, env_list, lines);
			break;
		case 2:
			_cd(line_vector, argv);
			break;
		case 3:
			_setenv(line_vector[1], line_vector[2], env_list);
			break;
		case 4:
			_setenv(line_vector[1], line_vector[2], env_list);
			break;
		default:
			return (-1);
	}
	return (0);
}

/**
 * _setenv - Sets an environment variable.
 * @name: The name of the environment variable to be set.
 * @value: The value to be assigned to the environment variable.
 * @env_list: A pointer to a linked list containing the environment variables.
 *
 * Return: void
 */
void _setenv(char *name, char *value, list_path *env_list)
{
	list_path *var;
	char *full_var;
	int count;

	count = _strlen(name) + _strlen(value) + 2;
	full_var = malloc(count);
	if (full_var == NULL)
	{
		perror("setenv ERROR");
		/*
		* TODO status
		*/
		/*print something*/
	}
	full_var = _strcpy(full_var, name);
	full_var[_strlen(name)] = '=';
	full_var[_strlen(name) + 1] = '\0';
	full_var = _strcat(full_var, value);
	full_var[count - 1] = '\0';
	var = get_variable(name, env_list);

	if (var == 0)
	{
		free(var->path);
		var->path = full_var;
		var->len = _strlen(full_var);
	}
	else
	{
		add_node(&env_list, full_var);
		var->len = _strlen(full_var);
	}

	print_list(env_list);

}

