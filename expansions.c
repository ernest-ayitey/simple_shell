#include "shell.h"

/**
 * expand_variables - expand variables in the input line
 * @data: a pointer to a struct of the program's data
 *
 * This function replaces variables in the input line with their values.
 * Currently, it supports replacing $?, $$, and environment variables.
 */
void expand_variables(data_of_program *data) {
    if (data->input_line == NULL)
        return;

    char line[BUFFER_SIZE] = {0};
    buffer_add(line, data->input_line);

    for (int i = 0; line[i]; i++) {
        if (line[i] == '#') {
            line[i] = '\0';
            break; // Stop processing after encountering a '#' character
        } else if (line[i] == '$') {
            if (line[i + 1] == '?') {
                // Replace $?
                line[i] = '\0';
                long_to_string(errno, line + i, 10);
                i += str_length(line + i) - 1; // Move 'i' to the end of the added string
            } else if (line[i + 1] == '$') {
                // Replace $$
                line[i] = '\0';
                long_to_string(getpid(), line + i, 10);
                i += str_length(line + i) - 1;
            } else if (line[i + 1] == ' ' || line[i + 1] == '\0') {
                // Skip '$ ' or '$' at the end of the line
                continue;
            } else {
                // Replace environment variables like $VAR
                int j;
                char expansion[BUFFER_SIZE] = {'\0'};
                for (j = 1; line[i + j] && line[i + j] != ' '; j++) {
                    expansion[j - 1] = line[i + j];
                }
                expansion[j - 1] = '\0';
                char *temp = env_get_key(expansion, data);
                line[i] = '\0';
                buffer_add(line, temp ? temp : "");
                buffer_add(line, line + i + j);
            }
        }
    }

    if (!str_compare(data->input_line, line, 0)) {
        free(data->input_line);
        data->input_line = str_duplicate(line);
    }
}

/**
 * expand_alias - expand aliases in the input line
 * @data: a pointer to a struct of the program's data
 *
 * This function replaces aliases in the input line with their values.
 */
void expand_alias(data_of_program *data) {
    if (data->input_line == NULL)
        return;

    char line[BUFFER_SIZE] = {0};
    buffer_add(line, data->input_line);

    int i = 0;
    while (line[i]) {
        int j = 0;
        char expansion[BUFFER_SIZE] = {'\0'};
        for (; line[i + j] && line[i + j] != ' '; j++) {
            expansion[j] = line[i + j];
        }
        expansion[j] = '\0';

        char *temp = get_alias(data, expansion);
        if (temp) {
            expansion[0] = '\0';
            buffer_add(expansion, line + i + j);
            line[i] = '\0';
            buffer_add(line, temp);
            buffer_add(line, expansion);
            break; // Stop after expanding the first alias
        }
        i += j;
        if (line[i] == ' ') {
            i++; // Move past spaces
        }
    }

    if (str_compare(data->input_line, line, 0) != 0) {
        free(data->input_line);
        data->input_line = str_duplicate(line);
    }
}

/**
 * buffer_add - append a string to the end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied into the buffer
 * Return: nothing
 */
void buffer_add(char *buffer, const char *str_to_add) {
    int length = str_length(buffer);
    str_copy(buffer + length, str_to_add);
}
