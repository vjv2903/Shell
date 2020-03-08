
#include "shell.h"

void exec_cd(char *arg, char **args)
{
    if (strcmp(args[1], ".") == 0)
        return;
    else if (args[1][0] == '\0' || strcmp(args[1], "~") == 0)
        chdir(home);
    else if (args[1][0] == '~')
    {
        args[1] += 2;
        char *path;
        path = (char *)malloc(1024 * sizeof(char));
        if (!path)
        {
            perror("Memory");
            return;
        }
        sprintf(path, "%s/%s", home, args[1]);
        if (chdir(path) < 0)
            perror("Error");
    }
    else if ((args[1][0] == '/' && chdir(args[1]) < 0) || chdir(args[1]) < 0)
        perror("Error");
}
