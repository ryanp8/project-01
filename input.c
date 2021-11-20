#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "input.h"
#include "util.h"

char *readln() {
    char *buffer = malloc(256);
    fgets(buffer, 256, stdin);
    return buffer;
}

char **parse_args(char *line) {
    int spaces = charcount(line, ' ');
    char **args = calloc(spaces + 2, sizeof(char*));
    char *token;
    int i = 0;
    while (line) {
        token = strsep(&line, " ");
        args[i] = token;
        i++;
    }
    return args;
}