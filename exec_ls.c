
#include "shell.h"

void disp_line_ls(char *filepath, char *filename)
{
    struct stat file_status;
    char date[10];
    int r = stat(filepath, &file_status);
    if (r < 0)
    {
        perror("Reading done wrong");
        return;
    }
    char *buffer;
    buffer = malloc(1024 * sizeof(char));
    if (!buffer)
    {
        perror("MEMORY");
        return;
    }
    char *s = buffer;
    int str_len = 0;
    char l;
    if (S_ISREG(file_status.st_mode))
        l = '-';
    else if (S_ISDIR(file_status.st_mode))
        l = 'd';
    else if (S_ISCHR(file_status.st_mode))
        l = 'c';
    else if (S_ISBLK(file_status.st_mode))
        l = 'b';
    else if (S_ISFIFO(file_status.st_mode))
        l = 'f';
    else if (S_ISLNK(file_status.st_mode))
        l = 'l';
    else
        l = 's';
    *s++ = l;
    str_len++;
    *s++ = (file_status.st_mode & S_IRUSR) ? 'r' : '-';
    str_len++;
    *s++ = (file_status.st_mode & S_IWUSR) ? 'w' : '-';
    str_len++;
    *s++ = (file_status.st_mode & S_IXUSR) ? 'x' : '-';
    str_len++;
    *s++ = (file_status.st_mode & S_IRGRP) ? 'r' : '-';
    str_len++;
    *s++ = (file_status.st_mode & S_IWGRP) ? 'w' : '-';
    str_len++;
    *s++ = (file_status.st_mode & S_IXGRP) ? 'x' : '-';
    str_len++;
    *s++ = (file_status.st_mode & S_IROTH) ? 'r' : '-';
    str_len++;
    *s++ = (file_status.st_mode & S_IWOTH) ? 'w' : '-';
    str_len++;
    *s++ = (file_status.st_mode & S_IXOTH) ? 'x' : '-';
    str_len++;
    *s++ = ' ';
    str_len++;
    *s++ = '\0';
    str_len++;
    write(1, buffer, strlen(buffer));
    free(buffer);
    buffer = malloc(1024 * sizeof(char));
    if (!buffer)
    {
        perror("MEMORY");
        return;
    }
    struct passwd *pw = getpwuid(file_status.st_uid);
    struct group *gr = getgrgid(file_status.st_gid);
    str_len++;
    if (pw == 0 || gr == 0)
    {
        perror("Error : User or group not found");
        return;
    }
    strftime(date, 10, "%b %2d %2I:%2M", gmtime(&(file_status.st_mtime)));
    str_len++;
    sprintf(buffer, "%2zu %s %s %7zu %s %s\n", file_status.st_nlink, pw->pw_name, gr->gr_name, file_status.st_size, date, filename);
    write(1, buffer, strlen(buffer));
    free(buffer);
}
void exec_ls(char *arg, char **args)
{
    int l = 0, a = 0;
    char *current_dir;
    current_dir = NULL;
    struct dirent **namelist;
    for (int i = 1; args[i][0] != '\0' && args[i] != NULL; ++i)
    {
        if (l == 0 && a == 0 && (strcmp(args[i], "-la") == 0 || strcmp(args[i], "-al") == 0))
            l = a = 1;
        else if (l == 0 && strcmp(args[i], "-l") == 0)
            l = 1;
        else if (a == 0 && strcmp(args[i], "-a") == 0)
            a = 1;
        else if (current_dir == NULL && strcmp(args[i], "&") != 0)
            current_dir = args[i];
        else if (strcmp(args[i], "&") != 0)
        {
            write(1, "Invalid number/type of arguments", 33);
            return;
        }
    }
    if (current_dir == NULL)
        current_dir = ".";
    int n = scandir(current_dir, &namelist, NULL, alphasort);
    char *buffer = malloc(1024 * sizeof(char));
    char *file_path = (char *)malloc(sizeof(char) * 1024);
    if (!file_path || !buffer)
    {
        perror("MEMORY");
        return;
    }
    if (n < 0)
    {
        perror("scandir");
        return;
    }
    if (l == 0)
    {
        while (n--)
        {
            if (a == 1)
            {
                write(1, namelist[n]->d_name, strlen(namelist[n]->d_name));
                write(1, "\n", 2);
            }
            else if (namelist[n]->d_name[0] != '.')
            {
                write(1, namelist[n]->d_name, strlen(namelist[n]->d_name));
                write(1, "\n", 2);
            }
            free(namelist[n]);
        }
    }
    else
    {
        while (n--)
        {
            if (a == 1)
            {
                sprintf(file_path, "%s/%s", current_dir, namelist[n]->d_name);
                disp_line_ls(file_path, namelist[n]->d_name);
            }
            else if (namelist[n]->d_name[0] != '.')
            {
                sprintf(file_path, "%s/%s", current_dir, namelist[n]->d_name);
                disp_line_ls(file_path, namelist[n]->d_name);
            }
            free(namelist[n]);
        }
        free(namelist);
    }
    if (l == 0)
        write(1, "\n", 2);
    free(buffer);
}
