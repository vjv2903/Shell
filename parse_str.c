#include "shell.h"

char **parse_str(char *buffer, char sep)
{
    char **result = (char **)malloc(1024 * sizeof(char *));
    if (!result)
    {
        perror("memory");
        exit(0);
    }
    int rowno = 0, rn = 0;
    while (buffer[strlen(buffer) - 1] == ';')
        buffer[strlen(buffer) - 1] = '\0';
    while (buffer[0] == ';')
        buffer++;
    if (strcmp(buffer, "") == 0)
    {
        result[0] = (char *)malloc(1024 * sizeof(char));
        if (!result[0])
        {
            perror("memory");
            exit(0);
        }
        result[0][0] = '\0';
        return result;
    }
    for (int i = 0; i < strlen(buffer); i++)
    {
        result[rowno] = (char *)malloc(1024 * sizeof(char));
        if (!result[rowno])
        {
            perror("memory");
            exit(0);
        }
        int j = 0;
        while (buffer[i] != '\0' && buffer[i] != sep)
            result[rowno][j++] = buffer[i++];
        result[rowno][j] = '\0';
        if (buffer[i] == '\0')
            break;
        rowno++;
    }
    rowno++;
    result[rowno] = (char *)malloc(1024 * sizeof(char));
    if (!result[rowno])
    {
        perror("memory");
        exit(0);
    }
    result[rowno][0] = '\0';
    return result;
}
