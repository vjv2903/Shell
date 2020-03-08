#include "shell.h"
void interpret_and_exec_cmd(char *cmd)
{
    char **cmds = parse_str(cmd, ';');
    int idkk;
    for (int i = 0; cmds[i][0] != '\0' && cmds[i] != NULL; ++i)
    {
        char **args = parse_str(cmds[i], ' ');
        if (args[0][0] != '\0')
        {
            for (int j = 0; cmds[i][j] != '\0'; ++j)
                if (cmds[i][j] == '&')
                {
                    cmds[i][j] = '\0';
                    isbg = 1;
                    break;
                }
            if (strcmp(args[0], "exit") == 0)
            {
                write(1, "Bye bye\n", 9);
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(args[0], "echo") == 0)
            {
                for (int i = 1; args[i][0] != '\0' && args[i] != NULL; ++i)
                {
                    write(1, args[i], strlen(args[i]));
                    write(1, " ", 2);
                }
                write(1, "\n", 2);
            }
            else if (strcmp(args[0], "cd") == 0)
                exec_cd(args[0], args);
            else if (strcmp(args[0], "pwd") == 0)
            {
                if (args[1][0] != '\0')
                {
                    write(1, "pwd: too many arguments\n", 25);
                    return;
                }
                char *buffer = (char *)malloc((1024) * sizeof(char));
                if (!buffer)
                {
                    perror("Memory");
                    return;
                }
                getcwd(buffer, 1024);
                write(1, buffer, strlen(buffer));
                write(1, "\n", 2);
                free(buffer);
            }
            else if (strcmp(args[0], "ls") == 0)
                exec_ls(args[0], args);
            else if (strcmp(args[0], "pinfo") == 0)
                exec_pinfo(args[0], args);
            else
            {
                int pid = fork();
                if (pid == 0)
                {
                    if (isbg)
                        setpgid(0, 0);
                    int i = 0;
                    while (args[i][0])
                        i++;
                    args[i] = NULL;
                    if (strcmp(args[i - 1], "&") == 0)
                    {
                        isbg = 1;
                        args[i - 1] = NULL;
                    }
                    if (execvp(args[0], args) < 0)
                    {
                        perror("Error: Command not found");
                        return;
                    }
                    exit(0);
                }
                else if (isbg == 0)
                    waitpid(pid, &idkk, WUNTRACED);
                else
                {
                    strcpy(running[size_running_procs].pname, args[0]);
                    running[size_running_procs++].pid = pid;
                }
            }
        }
    }
}