# Shell
Developed Shell to perform basic commands in C
The following are the specifications for the project. For each of the requirement, an appropriate example
is given along with it.
## Specification 1: Display requirement
When you execute your code a shell prompt of
the following form must appear:
<username@system_name:curr_dir>
### Example: 
<Name@UBUNTU:~>The directory from which the shell is invoked will be the home directory of the shell
and should be indicated by "~". If the user executes "cd" i.e change dir then the
corresponding change must be reflected in the shell as well.
### Example: ./a.out
<Name@UBUNTU:~>cd newdir
<Name@UBUNTU:~/newdir>
## Specification 2: Builtin commands
Builtin commands are contained within the shell itself. Checkout ‘type ​ commandname ​ ’ in the terminal
(eg. ‘type echo’). When the name of a builtin command is used as the first word of a simple command
the shell executes the command directly, without invoking another program. Builtin commands are
necessary to implement functionality impossible or inconvenient to obtain with separate utilities.
Make sure you implement  cd ,  pwd  and  echo . Don’t use ‘execvp’ or similar commands for implementing
these commands.
## Specification 3: ls command
Implement  ls [al]  – (it should be able to handle ls, ls -l, ls -a, ls -al/la and ls<Directoryname>. For ls , ls
-a and ls<Directoryname> outputting the entries in a single column is fine.
## Specification 4: System commands with and without arguments
All other commands are treated as system commands like : emacs, vi and so on. The shell must be able to
execute them either in the background or in the foreground.
Foreground processes  : For example, executing a "vi" command in the foreground implies that yourshell will wait for this process to complete and regain control when this process exits.
Background processes :  Any command invoked with "&" is treated as background command.
This implies that your shell will spawn that process and doesn't wait for the process to exit. It
will keep taking user commands.
### Example:
<Name@UBUNTU:~>ls &
This command when finished, should print result to stdout.
<Name@UBUNTU:~>emacs &
<Name@UBUNTU:~>ls -l -a ( Make sure all the given flags are executed properly for any command
and not just ls.) 
Execute other commands
<Name@UBUNTU:~> echo hello
## Specification 5: pinfo command (user defined)
- pinfo  : prints the process related info of your shell program.
### Example:
<Name@UBUNTU:~>pinfo
pid -- 231
Process Status -- {R/S/S+/Z}
memory  --  67854
{ Virtual Memory }
Executable Path --  ~/a.out
- pinfo <pid>  : prints the process info about given pid.
### Example:
<Name@UBUNTU:~>pinfo 7777
pid -- 7777
Process Status -- {R/S/S+/Z}
memory  --
123456 { Virtual Memory }
Executable Path -- /usr/bin/gcc
## Specification 6: Finished Background Processes
If the background process exits then the shell must display the appropriate message to the user.
### Example:
After emacs exits, your shell program should check the exit status of emacs and print it on stderr.
<Name@UBUNTU:~>.
emacs with pid 456 exited normally
<Name@UBUNTU:~>
