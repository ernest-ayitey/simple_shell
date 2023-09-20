#include "shell.h"

/**
 * tokenize - tokenize a string using a specified delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(data_of_program *data)
{
    const char *delimiter = " \t";
    int i, counter = 2;

    // Remove newline character if it exists
    int length = str_length(data->input_line);
    if (length > 0 && data->input_line[length - 1] == '\n')
        data->input_line[length - 1] = '\0';

    // Count the number of tokens
    for (i = 0; data->input_line[i]; i++)
    {
        for (int j = 0; delimiter[j]; j++)
        {
            if (data->input_line[i] == delimiter[j])
                counter++;
        }
    }

    // Allocate memory for tokens
    data->tokens = malloc(counter * sizeof(char *));
    if (data->tokens == NULL)
    {
        perror(data->program_name);
        exit(errno);
    }

    // Tokenize the input line
    i = 0;
    char *token = _strtok(data->input_line, delimiter);
    data->command_name = str_duplicate(token);

    while (token)
    {
        data->tokens[i++] = str_duplicate(token);
        token = _strtok(NULL, delimiter);
    }
}
