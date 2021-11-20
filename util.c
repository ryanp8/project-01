#include <string.h>
#include <ctype.h>

#include "util.h"

// function borrowed from stackoverflow
// https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
// by Adam Rosenfield
char *trim(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && (isspace((unsigned char)*end) || (unsigned char)*end == '\n'))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

int charcount(char *line, char c) {
    int count = 0;
    int j;
    int len = strlen(line);
    for (j = 0; j < len; j++) {
        if (line[j] == c) {
            count++;
        }
    }
    return count;
}