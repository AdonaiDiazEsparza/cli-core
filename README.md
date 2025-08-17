# CLI-core: Portable CLI for Embedded Systems
CLI-core is a lightweight and highly portable C library designed to help developers build Command-Line Interfaces (CLIs) for embedded systems. This core provides a set of modular functions that can be easily integrated into any firmware, allowing for seamless user interaction and device control over various communication protocols.

By separating the core logic from the communication layer, CLI-core enables developers to adapt the CLI to their specific needs. Whether you're using UART, USB, or other custom communication protocols, this library can be easily interfaced to provide a robust and extensible CLI for your project.

>[!CAUTION]
>This repository and core is still on development, do not use for new projects


## Key Features

**Portable C Code:** Written in standard C, ensuring high portability across different architectures and compilers.

**Protocol Agnostic:** The core logic is decoupled from the communication protocol, making it adaptable to UART, USB, or any other data stream.

**Modular Design:** The library provides a foundation for parsing commands and dispatching functions, allowing you to easily add or remove commands.

**Low Memory Footprint:** Designed with embedded systems in mind, it has a minimal memory and resource overhead.

**Easy Integration:** Simple API for quick integration into existing firmware.


## How to start?

Follow these steps to create and register your own CLI commands:

### **Step 1 – Define the command structure**

Every command is represented by a `cli_command_t`.  
This struct contains the command text, help description, and the callbacks that define its behavior.

```c
// Command structure definition
typedef struct
{
    char command_text[MAX_LEN_COMMAND];
    char text_help[HELP_LEN];
    cli_calls_for_execute_t command_execute_callback;
    cli_calls_for_event_t command_event_callback;
    cli_calls_for_exit_t command_exit_callback;
} cli_command_t;
```

### Step 2 – Write your callbacks

Each command must implement the following functions:

- Execute callback → runs when the command is invoked.
```c
void my_command_execute(void* context) {
    printf("Command executed!\n");
}
```

- Event callback → runs when the command is active and receives additional input.
```c
bool my_command_event(void* context, const char* data) {
    printf("Command event: %s\n", data);
    return true; // return false if the event is not handled
}
```

- Exit callback → runs when the command exits or is terminated.
```c
void my_command_exit(void* context) {
    printf("Command finished.\n");
}
```

### Step 3 – Create the command instance

Fill the struct with your command definition:

```c
cli_command_t my_command = {
    .command_text = "mycmd",
    .text_help = "This is my test command",
    .command_execute_callback = my_command_execute,
    .command_event_callback = my_command_event,
    .command_exit_callback = my_command_exit
};
```

### Step 4 – Register the command(s)

You can register commands in two ways:

- Add a list of commands at once:

```c
cli_command_t commands[] = { my_command, other_command };
cli_set_commands(&cli, commands, 2);
```

- Add commands individually:
```c
cli_add_command(&cli, my_command);
```

### Step 5 - Set the callbacks for the cli

The CLI needs two callbacks for essential work. One to display the text on terminal, and other to display the general help for the user. These functions are implement with ```cli_set_print_callbck``` and ```cli_set_help_callback```.
For example:
```c
cli_set_print_callback(&cli, my_print_function);

cli_set_help_callback(&cli, my_general_help_function);
```

### Step 6 - Run CLI

And that's all the process you need, run the cli with ```cli_process_input```. To run the cli needs to be on loop (like while), for example the next code received the text from terminal and pass teh string values to the cli function:
```c
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


