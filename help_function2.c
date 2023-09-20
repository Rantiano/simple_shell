#include "shell.h"

/**
 * get_variable - Searches for an environ variable by name in a linked list.
 * @name: The name of the environment variable to search for in a list.
 * @head: Pointer to the head of a linked list that contains environ variables.
 *
 * Return: A pointer to the node that represents the matching environ variable
 *         if found, or NULL if no matching variable is found in the list.
 */
list_path *get_variable(char *name, list_path *head)
{
	while (head)
	{
		if (_varcmp(name, head->path))
			return (head);
		head = head->next;
	}

	return (NULL);
}

/**
 * _varcmp - This compares a variable name with a full environ variable string.
 * @var_name: A pointer to a string that contains variable name to be compared.
 * @full_var: A pointer to a string that contains full environment variable.
 *
 * Return: 0 if there is a match success, or -1 if there is a mismatch.
 */
int _varcmp(char *var_name, char *full_var)
{
	int i;

	for (i = 0; var_name[i]; i++)
	{
		if (full_var[i])
			if (var_name[i] - full_var[i] != 0)
				return (-1);
	}
	if (full_var[i] == '=')
		return (0);

	return (-1);
}

/**
 * num_to_char - Converts an integer num to a character string.
 * @num: The integer value to be converted to a character string.
 *
 * Return: A pointer to a char string representation of the input int,
 *         or NULL on memory allocation failure.
 */
char *num_to_char(int num)
{
	/*count digits*/
	int c = 0, tmp = num;
	char *cp_num;

	if (num == 0)
	{
		c = 1;
	}
	else
	{
		while (tmp != 0)
		{
			tmp /= 10;
			c++;
		}
	}

	cp_num = malloc(sizeof(char) * (c + 1));
	if (!cp_num)
	{
		perror("malloc");
		return (NULL);
	}
	cp_num[c] = '\0';
	while (c != 0)
	{
		c--;
		cp_num[c] = '0' + num % 10;
		num /= 10;
	}

	return (cp_num);
}

/**
 * char_count_piped - Counts num of time a specified char occurs in a string.
 * @str: A pointer to a null-terminated string to be searched for.
 * @c: The character to be counted within the string.
 *
 * Return: The num of occurrences of the specified character in the string.
 */
unsigned int char_count_piped(char *str, char c)
{
	unsigned int count = 0;

	while (*str != '\0')
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count + 1);
}

