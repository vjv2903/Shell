
#include "shell.h"

int main()
{
    size_running_procs = 0;
    char *current_dir, *buffer, *pname;
    current_dir = (char *)malloc(1024 * sizeof(char));
    buffer = (char *)malloc(1024 * sizeof(char));
    if (!current_dir || !buffer)
    {
        perror("Memory");
        exit(0);
    }
    strcpy(current_dir, "~");
    getcwd(home, 1024);
    int k = 0, pid, status;
    while (k + 1 == 1)
    {
        while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
        {
            if (WIFEXITED(status))
            {
                int i = 0;
                while (i < size_running_procs)
                {
                    if (running[i].pid - pid == 0)
                    {
                        running[i].pid = -1;
                        pname = running[i].pname;
                        fprintf(stderr, "%s with pid %d exited normally.\n", pname, (int)pid);
                        break;
                    }
                    i++;
                }
            }
            if (WIFSIGNALED(status))
            {
                int i = 0;
                while (i < size_running_procs)
                {
                    if (running[i].pid - pid == 0)
                    {
                        running[i].pid = -1;
                        pname = running[i].pname;
                        fprintf(stderr, "%s with pid %d terminated by a signal.\n", pname, (int)pid);
                        break;
                    }
                    i++;
                }
            }
        }
        display_shell_prompt();
        readcmd(buffer);
        interpret_and_exec_cmd(buffer);
    }
    free(buffer);
    free(current_dir);
}
