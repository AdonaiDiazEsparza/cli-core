# CLI-core: Portable CLI for Embedded Systems
CLI-core is a lightweight and highly portable C library designed to help developers build Command-Line Interfaces (CLIs) for embedded systems. This core provides a set of modular functions that can be easily integrated into any firmware, allowing for seamless user interaction and device control over various communication protocols.

By separating the core logic from the communication layer, CLI-core enables developers to adapt the CLI to their specific needs. Whether you're using UART, USB, or other custom communication protocols, this library can be easily interfaced to provide a robust and extensible CLI for your project.

>[!CAUTION]
>This repository and core is still on development, do not use for new projects

---

## Key Features
**Portable C Code:** Written in standard C, ensuring high portability across different architectures and compilers.
**Protocol Agnostic:** The core logic is decoupled from the communication protocol, making it adaptable to UART, USB, or any other data stream.
**Modular Design:** The library provides a foundation for parsing commands and dispatching functions, allowing you to easily add or remove commands.
**Low Memory Footprint:** Designed with embedded systems in mind, it has a minimal memory and resource overhead.
**Easy Integration:** Simple API for quick integration into existing firmware.
