
#include "shell.h"
void display_shell_prompt()
{
    char *username, *system_name, *current_directory, *s, *buffer;
    username = (char *)malloc(1024 * sizeof(char));
    system_name = (char *)malloc(1024 * sizeof(char));
    current_directory = (char *)malloc(1024 * sizeof(char));
    buffer = (char *)malloc((1024 + 1024 + 1024 + 5) * sizeof(char));
    if (!system_name || !current_directory || !buffer)
    {
        perror("MEMORY");
        return;
    }
    gethostname(system_name, 1024);
    getlogin_r(username, 1024);
    getcwd(current_directory, 1024);
    int j = strlen(home);
    if (strncmp(current_directory, home, j) == 0)
    {
        s = current_directory;
        *s++ = '~';
        while (current_directory[j])
            *s++ = current_directory[j++];
        *s = '\0';
    }
    sprintf(buffer, "<%s@%s:%s>", username, system_name, current_directory);
    write(1, buffer, strlen(buffer));
    free(buffer);
    free(username);
    free(system_name);
    free(current_directory);
}
