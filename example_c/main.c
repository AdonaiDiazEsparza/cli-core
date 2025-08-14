#include <stdio.h>
#include "stdarg.h"
#include "cli_core.h"

#define UNUSED(X) (void)(X)

// ===============================================
//              FUNCTIONS CALLS FOR FIRST COMMAND
// ===============================================

void first_command_help(void *context);
void first_command_execute(void *context);
bool first_command_event(void *context, const char *data);
void first_command_exit(void *context);

// ===============================================
//              FUNCTIONS CALLS FOR SECOND COMMAND
// ===============================================

void second_command_help(void *context);
void second_command_execute(void *context);
bool second_command_event(void *context, const char *data);
void second_command_exit(void *context);

// ===============================================
//              FUNCTIONS CALLS FOR LAST COMMAND
// ===============================================

void command_added_help(void *context);
void command_added_execute(void *context);
bool command_added_event(void *context, const char *data);
void command_added_exit(void *context);

// ===============================================
//              FUNCTION FOR GENERAL HELP
// ===============================================

void general_help(void *context);

// ===============================================
//              FUNCTION TO PRINT FORMAT
// ===============================================

void print_func(const char *format, ...);

// ===============================================
//              CLI STRUCT
// ===============================================

cli_struct_t cli = {0};

// ===============================================
//              COMMANDS FOR CLI
// ===============================================

cli_command_t commands[2] = {
    {.command_text = "first_command",
     .text_help = "This is the first command\nShows the need it help for it",
     .command_execute_callback = first_command_execute,
     .command_event_callback = first_command_event,
     .command_exit_callback = first_command_exit},

    {.command_text = "second_command",
     .text_help = "This command shows 'Hello World!' on terminal",
     .command_execute_callback = second_command_execute,
     .command_event_callback = second_command_event,
     .command_exit_callback = second_command_exit},
};

cli_command_t command_to_add = {
    .command_text = "Added",
    .text_help = "This is the message for help in the last command\n this was added by the function 'cli_add_command'",
    .command_execute_callback = command_added_execute,
    .command_event_callback = command_added_event,
    .command_exit_callback = command_added_exit};

// ===============================================
//              MAIN FUNCTION
// ===============================================

int main()
{

    cli_set_commands(&cli, commands, 2);

    cli_add_command(&cli, command_to_add);

    cli_set_print_callback(&cli, print_func);

    cli_set_help_callback(&cli, general_help);

    char command_to_receive[64];

    while (true)
    {
        printf("> ");

        fgets(command_to_receive, sizeof(command_to_receive), stdin);
        
        size_t len = strlen(command_to_receive);
        if (len > 0 && command_to_receive[len-1] == '\n') {
            command_to_receive[len-1] = '\0';
        }

        cli_process_input(&cli, command_to_receive);
    }

    return 0;
}

// ===============================================
//              CALLBACKS FOR FIRST COMMAND
// ===============================================

void first_command_execute(void *context)
{
    UNUSED(context); // By the moment is not used

    print_func("When it is used to init or enter to the command!\nThis command will be in execution\n");

    cli_start_process(&cli);
}

bool first_command_event(void *context, const char *data)
{
    UNUSED(context); // By the moment is not used

    print_func("This is the function when the command is in execution\n");
    print_func("Data received in first command: %s\n", data);

    return false;
}

void first_command_exit(void *context)
{
    UNUSED(context); // By the moment is not used

    print_func("When you exit from the command execution\n");
}

// ===============================================
//              CALLBACKS FOR SECOND COMMAND
// ===============================================

void second_command_execute(void *context)
{
    UNUSED(context); // By the momemt is not used
    print_func("Hello World!\n");

    cli_stop_process(&cli);
}

bool second_command_event(void *context, const char *data)
{
    UNUSED(context); // By the momemt is not used
    UNUSED(data);
    return false;
}

void second_command_exit(void *context)
{
    UNUSED(context); // By the momemt is not used
}

// ===============================================
//              CALLBACKS FOR SECOND COMMAND
// ===============================================

void command_added_execute(void *context)
{
    UNUSED(context); // By the momemt is not used
    print_func("Last Command Added!\n");

    cli_stop_process(&cli);
}

bool command_added_event(void *context, const char *data)
{
    UNUSED(context); // By the momemt is not used
    UNUSED(data);
    return false;
}

void command_added_exit(void *context)
{
    UNUSED(context); // By the momemt is not used
}

// ===============================================
//              FUNCTION FOR GENERAL HELP
// ===============================================

void general_help(void *context)
{
    UNUSED(context); // By the momemt is not used

    printf("This function is for general help\nUse it to show message for you want\n");

    printf("The following commands are [%u]: \n", cli_get_commands_count(&cli));

    for(uint16_t i = 0; i<cli_get_commands_count(&cli); i++){
        printf("- %s\n", cli.commands[i].command_text);
    }
}

// ===============================================
//              FUNCTION TO PRINT DATA
// ===============================================

void print_func(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}