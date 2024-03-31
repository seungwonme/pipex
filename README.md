# pipex

The `pipex` project is part of the 42 school curriculum, challenging students to implement a simplified version of the shell command-line construct `< file1 cmd1 | cmd2 > file2`. This project aims to improve understanding of file descriptors, processes, and the concept of pipes in Unix-like operating systems.

## Overview

The `pipex` program is designed to take two commands as arguments and execute them in a way that mimics the behavior of the shell command `< file1 cmd1 | cmd2 > file2`. Key features include:

- **Piping**: Connects the standard output of the first command to the standard input of the second command using pipes.
- **Redirection**: Redirects the standard input or output to specified files as indicated in the command line.
- **Multiple processes**: Spawns and manages multiple child processes to execute the given commands in sequence.
- **Here documents**: Supports the use of here documents as input for the first command.

## Usage
1. Clone the project:
```bash
git clone https://github.com/seungwonme/pipex.git
```

2. Navigate to the project directory:
```bash
cd pipex
```

3. Compile the executable:
```bash
make
```

4. Run the program with the desired command-line arguments:
```bash
./pipex infile cmd1 cmd2 ... cmdn outfile
# It will execute the following command:
< infile cmd1 | cmd2 | ... | cmdn > outfile

./pipex here_doc <limiter> cmd1 cmd2 ... cmdn outfile
# It will execute the following command:
<< <limiter> cmd1 | cmd2 | ... | cmdn > outfile
```

Example:
```bash
./pipex infile "ls -l" "cat -e" "grep pipex" outfile
```

- To clean up object files:
```bash
make clean
```

- To delete all build files:
```bash
make fclean
```

- To clean and rebuild the executable:
```bash
make re
```
