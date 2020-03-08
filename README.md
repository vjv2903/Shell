# Shell
Developed Shell to perform basic commands in C
The following are the specifications for the project. For each of the requirement, an appropriate example
is given along with it.

## Aim

Implement a shell which supports semi-colon separated list of commands.

## How to run

Run the following commands in the terminal

```
make
./shell
```

## Files used

### main.c

The main file, contains the code to run the main infinite loop for the shell. It also displays the finished background processes (Specification 6) by checking for signals that indicate whether the child is dead or not.

### display_shell_prompt.c

This file contains the code to display the shell prompt as <username@system_name:curr_dir> (Specification 1)

### interpret_cmd.c

This file contains the code to interpret the command, i.e. the line entered. It parses the line entered into different commands on the basis of semicolons and then into different arguments based on spaces. In case, the command entered is exit, echo or pwd, the command is executed without calling any external function (Specification 2). For other built-ins, like cd, ls and pinfo, external functions are used (Specification 3). It also executes external commands using exec (Specification 4) in both foreground and background manner.

### exec_cd.c

This file implements cd command in the shell. (Specification 2)

### exec_ls.c

This file implements ls command in the shell. (Specification 3)  
Accepted tags: -l -a -la -al

### exec_pinfo.c

This file implements pinfo command in the shell. (Specification 5)

### parse_str.c

This file contains the code to parse the string, i.e. break down a long string into substrings, based on a separator. (used in interpret_cmd)

### readcmd.c

This file contains the code to read the input line from the shell. It trims as it reads.

### shell.h

A header file containing the function prototypes and global variables
