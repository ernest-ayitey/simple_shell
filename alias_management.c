#include "shell.h"

/**
 * print_alias - Display, add, remove, or show aliases.
 * @data: Pointer to the program's data structure.
 * @alias: Name of the alias to be printed.
 *
 * Return: 0 for success, or another number if specified in the arguments.
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
						&& data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
					{
						break;
					}
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}
	return (0);
}
/**
 * get_alias - Get the value of a specified alias.
 * @data: Pointer to the program's data structure.
 * @name: Name of the requested alias.
 *
 * Return: The value of the alias if found, or NULL if not found.
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, alias_length;
	/* Validate the arguments */
	if (name == NULL || data->alias_list == NULL)
	{
		return (NULL);
	}
	alias_length = str_length(name);
	for (i = 0; data->alias_list[i]; i++)
	{
		if (str_compare(name, data->alias_list[i], alias_length)
				&& data->alias_list[i][alias_length] == '=')
		{
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	return (NULL);
}
/**
 * set_alias - Add or override an alias.
 * @alias_string: Alias to be set in the form (name='value').
 * @data: Pointer to the program's data structure.
 *
 * Return: 0 for success, or 1 if an error occurred.
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL || data->alias_list == NULL)
	{
		return (1);
	}
	for (i = 0; alias_string[i] && alias_string[i] != '='; i++)
	{
		buffer[i] = alias_string[i];
	}
	if (alias_string[i] == '=')
	{
		temp = get_alias(data, alias_string + i + 1);
	}
	for (j = 0; data->alias_list[j]; j++)
	{
		if (str_compare(buffer, data->alias_list[j], i)
				&& data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}
	}
	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	} else
	{
		data->alias_list[j] = str_duplicate(alias_string);
	}
	return (0);
}
