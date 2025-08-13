#include "cli_core.h"

// Configurar funcion callback de ayuda
bool cli_set_help_callback(cli_struct_t *cli_struct, cli_help_t help_callback)
{
    if (!cli_struct)
        return false;
    cli_struct->cli_help = help_callback;
    return true;
}

// Configurar funcion callback para imprimir datos
bool cli_set_print_callback(cli_struct_t *cli_struct, cli_print_t cli_print_callback)
{
    if (!cli_struct)
        return false;
    cli_struct->cli_print = cli_print_callback;
    return true;
}

// Configurar array the funciones
bool cli_set_work_handle_callbacks(cli_struct_t *cli_struct, cli_calls_t cli_calls)
{
    if(!cli_struct) return false;
    cli_struct->calls_for_work = cli_calls;
    return true;
}

// Forzar finalizado de proceso
void cli_forced_exit_process(cli_struct_t *cli_struct)
{
    cli_struct->calls_for_work.exit[cli_struct->actual_command](cli_struct->context);
    cli_struct->process_running = false;
}

// Funcion para para poner que un comando este en proceso
void cli_set_in_process_command(cli_struct_t *cli_struct)
{
    cli_struct->process_running = true;
}

// Proceso General del Cli
void cli_process_input(cli_struct_t *cli_struct, const char *input)
{
    if (cli_struct->process_running && strncmp(input, "exit", 4) == 0)
    {
        cli_forced_exit_process(cli_struct);
        return;
    }

    else if (cli_struct->process_running)
    {
        cli_struct->calls_for_work.event[cli_struct->actual_command](cli_struct->context, input);
        return;
    }

    if (strncmp(input, "help ", 5) == 0)
    {
        const char *cmd = input + 5;
        for (uint32_t i = 0; i < cli_struct->count_of_commands; i++)
        {
            if (strcmp(cmd, cli_struct->text_commands[i]) == 0)
            {
                cli_struct->calls_for_work.help[i](cli_struct->context);
                return;
            }
        }
        cli_struct->cli_print("Comando '%s' no encontrado.\r\n", cmd);
        cli_struct->cli_help();
        return;
    }

    else if (strncmp(input, "help", 4) == 0)
    {
        cli_struct->cli_help();
        return;
    }

    for (uint32_t i = 0; i < cli_struct->count_of_commands; i++)
    {
        if (strcmp(input, cli_struct->text_commands[i]) == 0)
        {
            cli_struct->actual_command = i;
            cli_struct->calls_for_work.execute[i](cli_struct->context);
            return;
        }
    }

    cli_struct->cli_print("Comando no reconocido: %s\r\n", input);
    cli_struct->cli_help();
}
