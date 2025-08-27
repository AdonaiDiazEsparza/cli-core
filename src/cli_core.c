#include "cli_core.h"

// Set general help callback
bool cli_set_help_callback(cli_struct_t *cli_struct, cli_help_t help_callback)
{
    if (!cli_struct)
        return false;
    cli_struct->cli_help = help_callback;
    return true;
}

// Set the print callback
bool cli_set_print_callback(cli_struct_t *cli_struct, cli_print_t cli_print_callback)
{
    if (!cli_struct)
        return false;
    cli_struct->cli_print = cli_print_callback;
    return true;
}

// Set the context for the CLI
void cli_set_context(cli_struct_t *cli_struct, void *context){

    if(!context) return;

    cli_struct->context = context;
}

// Forced to finalize a process 
void cli_forced_exit_process(cli_struct_t *cli_struct)
{
    // Si no existe funcion de exit
    if (cli_struct->commands[cli_struct->actual_command].command_exit_callback == 0)
    {
        cli_struct->cli_print("Exit callback doesnt exist\n");
        return;
    }

    cli_struct->commands[cli_struct->actual_command].command_exit_callback(cli_struct->context);
    cli_struct->process_running = false;
}

// Finish the process
void cli_stop_process(cli_struct_t *cli_struct)
{
    cli_struct->process_running = false;
}

// Start the process
void cli_start_process(cli_struct_t *cli_struct)
{
    cli_struct->process_running = true;
}

// Function to set all the commands for the CLI
void cli_set_commands(cli_struct_t *cli_struct, cli_command_t* commands, uint16_t count_of_commands)
{
    if (!cli_struct || !commands || count_of_commands == 0)
        return;

    cli_command_t* tmp = realloc(cli_struct->commands, count_of_commands * sizeof(cli_command_t));
    if (!tmp) {
        return;
    }

    cli_struct->commands = tmp;
    memcpy(cli_struct->commands, commands, count_of_commands * sizeof(cli_command_t));
    cli_struct->count_of_commands = count_of_commands;
}

// Function to add a command
void cli_add_command(cli_struct_t *cli_struct, cli_command_t command)
{
    if (!cli_struct)
        return;

    cli_command_t* tmp = realloc(cli_struct->commands,
                                 (cli_struct->count_of_commands + 1) * sizeof(cli_command_t));
    if (!tmp) {
        return;
    }

    cli_struct->commands = tmp;
    cli_struct->commands[cli_struct->count_of_commands] = command;
    cli_struct->count_of_commands++;
}

// Function to add a block of commands
void cli_append_commands(cli_struct_t *cli_struct, cli_command_t* commands, uint16_t count_of_commands)
{
    if (!cli_struct || !commands || count_of_commands == 0)
        return;

    size_t new_count = cli_struct->count_of_commands + count_of_commands;

    cli_command_t* tmp = realloc(cli_struct->commands, new_count * sizeof(cli_command_t));
    if (!tmp) {
        return;
    }

    cli_struct->commands = tmp;
    memcpy(&cli_struct->commands[cli_struct->count_of_commands],
           commands,
           count_of_commands * sizeof(cli_command_t));

    cli_struct->count_of_commands = new_count;
}

// Function to get the commands count
uint16_t cli_get_commands_count(cli_struct_t *cli_struct)
{
    return cli_struct->count_of_commands;
}

// General process 
void cli_process_input(cli_struct_t *cli_struct, const char *input)
{
    if (cli_struct->process_running && strncmp(input, "exit", 4) == 0)
    {
        cli_forced_exit_process(cli_struct);
        return;
    }

    else if (cli_struct->process_running)
    {
        if (cli_struct->commands[cli_struct->actual_command].command_event_callback != 0)
        {
            cli_struct->commands[cli_struct->actual_command].command_event_callback(cli_struct->context, input);
        }
        else
        {
            cli_struct->process_running = false;
        }
        return;
    }

    if (strncmp(input, "help ", 5) == 0)
    {
        const char *cmd = input + 5;
        for (uint32_t i = 0; i < cli_struct->count_of_commands; i++)
        {
            if (strcmp(cmd, cli_struct->commands[i].command_text) == 0)
            {
                cli_struct->cli_print("%s\n", cli_struct->commands[i].text_help);
                return;
            }
        }
        cli_struct->cli_help(cli_struct->context);
        return;
    }

    else if (strncmp(input, "help", 4) == 0)
    {
        cli_struct->cli_help(cli_struct->context);
        return;
    }

    for (uint32_t i = 0; i < cli_struct->count_of_commands; i++)
    {
        if (strcmp(input, cli_struct->commands[i].command_text) == 0)
        {
            cli_struct->actual_command = i;

            if (cli_struct->commands[cli_struct->actual_command].command_execute_callback != 0)
            {
                cli_struct->commands[cli_struct->actual_command].command_execute_callback(cli_struct->context);
            }
            else
            {
                cli_struct->cli_print("Call for execute dosent exist\n");
            }
            return;
        }
    }

    cli_struct->cli_help(cli_struct->context);
}
