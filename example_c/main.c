#include <stdio.h>
#include "cli_core.h"

#define UNUSED(X) (void)(X)

// ===============================================

void first_command_help(void *context)
{
    UNUSED(context);
}

void first_command_execute(void *context)
{
    UNUSED(context);
}

bool first_command_event(void *context, const char *data)
{
    UNUSED(context);
    UNUSED(data);
    return false;
}

void first_command_exit(void *context)
{
    UNUSED(context);
}

// ===============================================

void second_command_help(void *context)
{
    UNUSED(context);
}

void second_command_execute(void *context)
{
    UNUSED(context);
}

bool second_command_event(void *context, const char *data)
{
    UNUSED(context);
    UNUSED(data);
    return false;
}

void second_command_exit(void *context)
{
    UNUSED(context);
}

// ===============================================

cli_struct_t cli = {0};

cli_command_t commands[2] = {
    {.command_text = "first_command",
     .command_help_callback = first_command_help,
     .command_execute_callback = first_command_execute,
     .command_event_callback = first_command_event,
     .command_exit_callback = first_command_exit},

    {.command_text = "second_command",
     .command_help_callback = second_command_help,
     .command_execute_callback = second_command_execute,
     .command_event_callback = second_command_event,
     .command_exit_callback = second_command_exit},
};

cli_command_t command_to_add = {
    .command_text = "Added"};

int main()
{

    cli_set_commands(&cli, commands, 2);

    cli_add_command(&cli, command_to_add);

    printf("Command [0] = %s\n", cli.commands[0].command_text);
    printf("Command [1] = %s\n", cli.commands[1].command_text);
    printf("Command [2] = %s\n", cli.commands[2].command_text);

    return 0;
}