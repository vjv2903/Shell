
#include "shell.h"

void readcmd(char *buffer)
{
    char ch = ' ';
    int cur = 0;
    while (1)
    {
        read(0, &ch, 1);
        if (ch == '\n' || ch == '\0')
        {
            buffer[0] = '\0';
            return;
        }
        else if (ch != ' ' && ch != '\v' && ch != '\t')
            break;
    }
    buffer[cur] = ch;
    cur = cur + 1;
    while (1)
    {
        if (ch == '\n' || ch == '\0')
            break;
        read(0, &ch, 1);
        if ((ch == ' ' || ch == '\v' || ch == '\t') && (ch != '\0' && ch != '\n'))
        {
            buffer[cur] = ch;
            cur = cur + 1;
            while ((ch == ' ' || ch == '\v' || ch == '\t') && (ch != '\0' && ch != '\n'))
                read(0, &ch, 1);
        }
        buffer[cur] = ch;
        cur = cur + 1;
    }
    cur--;
    while (buffer[cur] == ' ' || buffer[cur] == '\t' || buffer[cur] == '\v' || buffer[cur] == '\0' || buffer[cur] == '\n')
        cur--;
    buffer[cur + 1] = '\0';
    for (int i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == '\t' || buffer[i] == '\v')
            buffer[i] = ' ';
}
