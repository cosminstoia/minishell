# minishell
Welcome to Minishell, a simplified shell project created as part of the 42 School curriculum. The objective of this project was to collaborate in a team of two to create a minimalistic Unix shell capable of parsing and executing user input like a real shell, with essential features implemented. This project was a valuable exercise in system programming and understanding the internals of shell operations.
## Overview
Minishell is a basic command-line interpreter similar to bash, implemented in C. The shell is responsible for reading input, parsing it into commands, and executing these commands in an environment similar to that of a Unix-like operating system.
This project taught me the fundamentals of shell development, including process creation and management.
## Features
- Command execution, including relative and absolute paths.
- I/O redirection (>, >>, <).
- Pipes (|) for connecting commands.
- Environment variable handling ($VAR, env, export, unset).
- Signal handling for Ctrl-C, Ctrl-D, and Ctrl-\ for proper interactive shell behavior.
- History management.
- Simple error handling with appropriate messages.
## Installation
To install and run Minishell, follow these steps:
1. Clone this repository:
```c
git clone https://github.com/cosminstoia/minishell.git
```
2. Navigate into the project directory:
```c
cd minishell
```
3. Build the project using make:
```c
make
```
4. Runt he shell:
```c
./minishell
```
## Usage
Once you have the shell running, you can type commands just as you would in a normal shell.
Below are a few example commands:
```c
$ ls -l
$ echo "Hello, World!"
$ cd ..
$ pwd
$ export MY_VAR=value
$ echo $MY_VAR
$ cat file.txt | grep "text"
```
## Supported Built-ins
Minishell supports the following built-in commands:

``echo`` - Prints text to the terminal.

``cd`` - Changes the current working directory.

``pwd`` - Prints the current working directory.

``export`` - Sets environment variables.

``unset`` - Unsets environment variables.

``env`` - Prints the environment variables.

``exit`` - Exits the shell.

## Project Goals
The Minishell project was designed to help us achieve the following goals:

Deepen understanding of Unix-like operating system internals.
Implement basic process management with ``fork()``, ``execve()``, ``waitpid()``, and ``signal()``.
Build a functional interactive shell capable of managing job control, pipes, and redirections.
Improve our ability to work with system calls, file descriptors, and error handling.
Gain experience with memory management in C, ensuring proper allocation and deallocation throughout.
