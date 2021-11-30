#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "input.h"
#include "util.h"

char *readln() {
    char *buffer = malloc(256);
    char *res = fgets(buffer, 256, stdin);
    if (res) {
        return buffer;
    }
    return 0;
}

char **parse_args(char *input) {
    char **args = split(input, " ");
    return args;
}

char **parse_commands(char *input) {
    char **commands = split(input, ";");
    return commands;
}

char **parse_pipe(char *input) {
    char **pipes = split(input, "|");
    return pipes;
}

char **parse_stdout_redirect(char *input) {
    char **redirections = split(input, ">");
    return redirections;
}

char **parse_stdin_redirect(char *input) {
    char **redirections = split(input, "<");
    return redirections;
}

char **parse_append_stdout_redirect(char *input) {
    char **redirections = split(input, ">>");
    return redirections;
}
