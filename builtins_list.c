#include "shell.h"

int builtins_list(data_of_program *data)
{
    builtins options[] = {
        {"exit", builtin_exit},
        {"help", builtin_help},
        {"cd", builtin_cd},
        {"alias", builtin_alias},
        {"env", builtin_env},
        {"setenv", builtin_set_env},
        {"unsetenv", builtin_unset_env},
        {NULL, NULL}
    };

    for (int iterator = 0; options[iterator].builtin != NULL; iterator++) {
        if (str_compare(options[iterator].builtin, data->command_name, 0)) {
            return options[iterator].function(data);
        }
    }

    return -1;
}
