#include "shell.h"
/**
 *free_pointer - Frees a single pointer and sets it to NULL.
 * @ptr: Pointer to the memory to be freed and set NULL.
 * Return: Nothing
 */
void free_pointer(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/**
 * free_array_of_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void free_array_of_pointers(char ***array)
{
	if (*array != NULL)
	{
		for (int i = 0; (*array)[i]; i++)
		{
			free_pointer(&(*array)[i]);
		}
		free(*array);
		*array = NULL;
	}
}

/**
 * free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0 && close(data->file_descriptor) != 0)
	{
		perror(data->program_name);
	}
	free_pointer(&(data->input_line));
	free_pointer(&(data->command_name));
	free_array_of_pointers(&(data->env));
	free_array_of_pointers(&(data->alias_list));
}

