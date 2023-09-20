#include "shell.h"

/**
 * Frees a single pointer and sets it to NULL.
 */
void free_pointer(char **ptr) {
    if (*ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

/**
 * Frees an array of pointers and sets the array to NULL.
 */
void free_array_of_pointers(char ***array) {
    if (*array != NULL) {
        for (int i = 0; (*array)[i]; i++) {
            free_pointer(&(*array)[i]);
        }
        free(*array);
        *array = NULL;
    }
}

/**
 * Frees all the fields of the data structure.
 */
void free_all_data(data_of_program *data) {
    if (data->file_descriptor != 0 && close(data->file_descriptor) != 0) {
        perror(data->program_name);
    }
    free_pointer(&(data->input_line));
    free_pointer(&(data->command_name));
    free_array_of_pointers(&(data->env));
    free_array_of_pointers(&(data->alias_list));
}

