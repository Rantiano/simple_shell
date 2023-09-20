#include "shell.h"
/**
 * add_node - function adds a new node to a linked list.
 * @head: A pointer to a pointer to the first node of the linked list.
 * @path: The string data to be stored in the new node.
 *
 * Return: A pointer to the newly added node if node creation and memory
 *         allocation were successful, or NULL if otherwise.
 */

list_path *add_node(list_path **head, char *path)
{
	char *s_cpy;
	list_path *l;

	l = malloc(sizeof(list_path));
	if (l == NULL)
		return (NULL);

	if (path)
	{
		s_cpy = _strdup(path);
		if (s_cpy == NULL)
		{
			free(l);
			return (NULL);
		}
		l->path = s_cpy;
		l->len = _strlen(s_cpy);
	}
	else
	{
		l->path = NULL;
		l->len = 0;
	}
	l->next = (*head);
	*head = l;
	return (l);
}

/**
 * free_list - frees a linked list of the list_path nodes.
 * @head: pointer to a head pointer of the linked list.
 */
void free_list(list_path *head)
{

	if (head == NULL)
	{
		return;
	}

	free_list(head->next);
	if (head->path)
		free(head->path);

	free(head);
}

/**
 * set_all_paths_to_list - Extracts and stores all dir in the PATH environ var.
 *
 * Return: A pointer to head of the linked list containing PATH dir, or NULL
 *         if the PATH environ variable isn't set or memory allocation fails.
 */
list_path *set_all_paths_to_list()
{
	char *path_variable, *path_var_cpy, *token;
	list_path *paths_list;

	paths_list = NULL;

	path_variable = _getenv("PATH");
	if (path_variable == NULL)
		return (NULL);

	path_var_cpy = _strdup(path_variable);
	if (path_var_cpy == NULL)
		return (NULL);

	token = _strtok(path_var_cpy, ":");
	while (token != NULL)
	{
		add_node(&paths_list, token);
		token = _strtok(NULL, ":");
	}

	free(path_var_cpy);

	return (paths_list);
}

/**
 * set_all_vector_to_list - Converts the environ var to a linked list of str.
 *
 * Return: A pointer to the head of a linked list containing environ var.
 */
list_path *set_all_vector_to_list()
{
	char *path_var_cpy;
	list_path *paths_list;
	int i = 0;

	paths_list = NULL;

	if (environ == NULL)
		return (NULL);
	while (environ[i])
	{
		path_var_cpy = environ[i];
		if (path_var_cpy == NULL)
			return (NULL);
		add_node(&paths_list, path_var_cpy);
		i++;
	}
	return (paths_list);
}

/**
 * check_access - Checks if a command is executable in any dir from the PATH.
 * @line_av_1: The command to check for the executability.
 * @current: A pointer to the head of a linked list containing dir from PATH.
 *
 * Return: A pointer to the full path of the executable command if found,
 *         NULL if otherwise.
 */

char *check_access(char *line_av_1, list_path *current)
{
	char *full_path;
	int found = 0, len;

	if (current == NULL)
		return (NULL);
	while (current)
	{
		len = _strlen(current->path) + _strlen(line_av_1) + 2;

		if (len > 1024)
		{
			write(STDERR_FILENO, "ERROR: Path too long\n", 21);
			continue;
		}
		full_path = (char *)malloc(len * sizeof(char));
		_strcpy(full_path, current->path);
		_strcat(full_path, "/");
		_strcat(full_path, line_av_1);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break;
		}
		else
			free(full_path);

		current = current->next;
	}
	if (found)
		return (full_path);

	else
		return (NULL);
}

