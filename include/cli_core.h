#pragma once

/**
 * This is the core for the cli
 * Here I defined the necessary calls and the structs for the CLI
 * This will be used with the UART configuration and the USB configuration
 *
 * At the moment this is the first core for the cli
 * Version: 0.1
 * Date: July 5 2025
 * Author: Adonai Diaz (Donuts Diaz)
 */

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_COMMANDS 16565
#define MAX_LEN_COMMAND 64

// Tipos de funciones de comando
typedef void (*cli_calls_for_help_t)(void *context);
typedef void (*cli_calls_for_execute_t)(void *context);
typedef bool (*cli_calls_for_event_t)(void *context, const char *data);
typedef void (*cli_calls_for_exit_t)(void *context);

// Tipo de funciones para configuracion y comando
typedef void (*cli_print_t)(const char *format, ...); // Funcion para imprimir datos
typedef void (*cli_help_t)(void* context);                     // Funcion de llamado de help o ayud

// Estructura para cada comando
typedef struct
{
    char command_text[MAX_LEN_COMMAND];
    cli_calls_for_help_t command_help_callback;
    cli_calls_for_execute_t command_execute_callback;
    cli_calls_for_event_t command_event_callback;
    cli_calls_for_exit_t command_exit_callback;
} cli_command_t;

// Estructura general del CLI
typedef struct
{
    cli_command_t commands[MAX_COMMANDS]; // Array de estructura de comandos
    cli_print_t cli_print;                // Funcion para imprimir en cli
    cli_help_t cli_help;                  // Funcion para llamar a ayuda (help)
    void *context;                        // Contexto común
    uint16_t actual_command;              // Índice del comando actual ejecutado
    uint16_t count_of_commands;           // Total de comandos registrados
    bool process_running;                 // Para saber si un proceso esta corriendo
} cli_struct_t;

bool cli_set_help_callback(cli_struct_t *cli_struct, cli_help_t help_callback);
bool cli_set_print_callback(cli_struct_t *cli_struct, cli_print_t cli_print_callback);
void cli_set_commands(cli_struct_t *cli_struct, cli_command_t commands[], uint16_t count_of_commands);
void cli_add_command(cli_struct_t *cli_struct, cli_command_t command);
uint16_t cli_get_commands_count(cli_struct_t *cli_struct);
void cli_forced_exit_process(cli_struct_t *cli_struct);
void cli_stop_process(cli_struct_t *cli_struct);
void cli_start_process(cli_struct_t *cli_struct);
void cli_set_in_process_command(cli_struct_t *cli_struct);
void cli_process_input(cli_struct_t *cli_struct, const char *input);
