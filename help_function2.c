#include "shell.h"

/**
 * get_variable - .
 * @name: .
 * @head: .
 * Return: .
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
 * _varcmp - .
 * @var_name: .
 * @full_var: .
 * Return: .
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
 * num_to_char - .
 * @num: .
 * Return: .
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
 * char_count_piped - .
 * @str: .
 * @c: .
 * Return: .
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

