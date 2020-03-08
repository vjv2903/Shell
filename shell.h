#include <time.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <grp.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#ifndef SHELL_H

#define SHELL_H
char home[1024];
int isbg;
int size_running_procs;
struct P
{
    char pname[128];
    int pid;
} process;
struct P running[2048];
void display_shell_prompt();
void readcmd(char *buffer);
void interpret_and_exec_cmd(char *cmd);
void exec_exit(char *arg, char **args);
char **parse_str(char *buffer, char sep);
void exec_ls(char *arg, char **args);
void exec_pinfo(char *str, char **args);
void exec_cd(char *arg, char **args);

#endif