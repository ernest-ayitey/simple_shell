#include "shell.h"

int main(int argc, char *argv[], char *env[])
{
    data_of_program data_struct = { NULL }, *data = &data_struct;
    char *prompt = "";

    initialize_data(data, argc, argv, env);

    signal(SIGINT, handle_ctrl_c);

    if (is_interactive_mode(argc))
    {
        errno = 2;
        prompt = PROMPT_MSG;
    }
    
    errno = 0;
    run_shell(prompt, data);
    return 0;
}

void handle_ctrl_c(int opr UNUSED)
{
    _print("\n");
    _print(PROMPT_MSG);
}

void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
    data->program_name = argv[0];
    data->input_line = NULL;
    data->command_name = NULL;
    data->exec_counter = 0;

    if (argc == 1)
    {
        data->file_descriptor = STDIN_FILENO;
    }
    else
    {
        data->file_descriptor = open_file(argv[1]);
    }

    data->tokens = NULL;
    copy_environment(data, env);
    initialize_alias_list(data);
}

void run_shell(char *prompt, data_of_program *data)
{
    int error_code = 0, string_len = 0;

    while (++(data->exec_counter))
    {
        _print(prompt);
        error_code = string_len = _getline(data);

        if (error_code == EOF)
        {
            free_all_data(data);
            exit(errno);
        }

        if (string_len >= 1)
        {
            expand_alias(data);
            expand_variables(data);
            tokenize(data);

            if (data->tokens[0])
            {
                error_code = execute(data);

                if (error_code != 0)
                    _print_error(error_code, data);
            }

            free_recurrent_data(data);
        }
    }
}
