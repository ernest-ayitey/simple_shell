#include "shell.h"

/**
 * expand_variable - Helper function to expand variables in the input line.
 * @data: A pointer to a struct of the program's data.
 * @i: A pointer to the index being processed in the input line.
 * @line: The input line being processed.
 */
static void expand_variable(data_of_program *data, int *i, char *line);

/**
 * expand_regular_variable - Helper function to expand regular
 * variables in the input line.
 * @data: A pointer to a struct of the program's data.
 * @i: A pointer to the index being processed in the input line.
 * @line: The input line being processed.
 */
static void expand_regular_variable(data_of_program *data, int *i, char *line);

/**
 * expand_variables - Expand variables in the input line.
 * @data: A pointer to a struct of the program's data.
 *
 * This function replaces variables in the input line with their values.
 * Currently, it supports replacing $?, $$, and environment variables.
 */
void expand_variables(data_of_program *data)
{
	if (data->input_line == NULL)
		return;

	char line[BUFFER_SIZE] = {0};

	buffer_add(line, data->input_line);

	for (int i = 0; line[i]; i++)
	{
		if (line[i] == '#')
		{
			line[i] = '\0';
			break;
		} else if (line[i] == '$')
		{
			expand_variable(data, &i, line);
		}
	}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}
/**
 * expand_regular_variable - Helper function to expand
 * regular variables in the input line.
 * @data: A pointer to a struct of the program's data.
 * @i: A pointer to the index being processed in the input line.
 * @line: The input line being processed.
 */
static void expand_regular_variable(data_of_program *data, int *i, char *line)
{
	int j;
	char expansion[BUFFER_SIZE] = {'\0'};

	for (j = 1; line[*i + j] && line[*i + j] != ' '; j++)
	{
		expansion[j - 1] = line[*i + j];
	}
	expansion[j - 1] = '\0';

	char *temp = env_get_key(expansion, data);

	line[*i] = '\0';
	buffer_add(line, temp ? temp : "");
	buffer_add(line, line + *i + j);
}
/**
 * expand_alias - Expand aliases in the input line.
 * @data: A pointer to a struct of the program's data.
 *
 * This function replaces aliases in the input line with their values.
 */
void expand_alias(data_of_program *data)
{
	if (data->input_line == NULL)
		return;

	char line[BUFFER_SIZE] = {0};

	buffer_add(line, data->input_line);

	int i = 0;

	while (line[i])
	{
		int j = 0;
		char expansion[BUFFER_SIZE] = {'\0'};

		for (; line[i + j] && line[i + j] != ' '; j++)
		{
			expansion[j] = line[i + j];
		}
		expansion[j] = '\0';
		char *temp = get_alias(data, expansion);

		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + j);
			line[i] = '\0';
			buffer_add(line, temp);
			buffer_add(line, expansion);
			break;
		}
		i += j;

		if (line[i] == ' ')
		{
			i++;
		}
	}
	if (str_compare(data->input_line, line, 0) != 0)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}
/**
 * buffer_add - Append a string to the end of the buffer.
 * @buffer: Buffer to be filled.
 * @str_to_add: String to be copied into the buffer.
 */
void buffer_add(char *buffer, const char *str_to_add)
{
	int length = str_length(buffer);

	str_copy(buffer + length, str_to_add);
}
