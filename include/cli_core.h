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

#define MAX_COMMANDS 64
#define MAX_LEN_COMMAND 64
#define HELP_LEN 512

#ifdef __cplusplus
extern "C" {
#endif

// Definition for every command function
typedef void (*cli_calls_for_execute_t)(void *context);
typedef bool (*cli_calls_for_event_t)(void *context, const char *data);
typedef void (*cli_calls_for_exit_t)(void *context);

// Tipo de funciones para configuracion y comando
typedef void (*cli_print_t)(const char *format, ...); // Definition for function to print text on CLI
typedef void (*cli_help_t)(void *context);            // Definition for function to display the general help

// CLI command struct
typedef struct
{
    char command_text[MAX_LEN_COMMAND];
    char text_help[HELP_LEN];
    cli_calls_for_execute_t command_execute_callback;
    cli_calls_for_event_t command_event_callback;
    cli_calls_for_exit_t command_exit_callback;
} cli_command_t;

// General Struct for teh CLI
typedef struct
{
    cli_command_t commands[MAX_COMMANDS]; // Array for the commands struct
    cli_print_t cli_print;                // Function to print text on the CLI terminal
    cli_help_t cli_help;                  // Function for general help
    void *context;                        // Context
    uint16_t actual_command;              // Current command in process
    uint16_t count_of_commands;           // Total of commands
    bool process_running;                 // Variable for process running
} cli_struct_t;

bool cli_set_help_callback(cli_struct_t *cli_struct, cli_help_t help_callback);
bool cli_set_print_callback(cli_struct_t *cli_struct, cli_print_t cli_print_callback);
void cli_set_commands(cli_struct_t *cli_struct, cli_command_t commands[], uint16_t count_of_commands);
void cli_add_command(cli_struct_t *cli_struct, cli_command_t command);
void cli_set_context(cli_struct_t *cli_struct, void *context);
uint16_t cli_get_commands_count(cli_struct_t *cli_struct);
void cli_forced_exit_process(cli_struct_t *cli_struct);
void cli_stop_process(cli_struct_t *cli_struct);
void cli_start_process(cli_struct_t *cli_struct);
void cli_process_input(cli_struct_t *cli_struct, const char *input);

#ifdef __cplusplus
extern "C" {
#endif
