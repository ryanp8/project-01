#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#include "trim.h"

char **parse_args(char *line) {
    int spaces = 0;
    int j;
    int len = strlen(line);
    for (j = 0; j < len; j++) {
        if (line[j] == ' ') {
            spaces++;
        }
    }
    char **args = calloc(spaces + 1, sizeof(char*));
    char *token;
    int i = 0;
    while (line) {
        token = strsep(&line, " ");
        args[i] = token;
        i++;
    }
    return args;
}

char *readln() {
    char *buffer = malloc(256);
    fgets(buffer, 256, stdin);
    return buffer;
}


void print_prompt() {
    printf("$ ");
}

int run_proc(char **args) {
    int f = fork();
    if (f) {
        int w, status;
        w = waitpid(f, &status, 0);
    }
    else {
        return execvp(args[0], args);
    }
    return 0;
}

int main() {

    while (1) {
        print_prompt();
        char *line = readln();
        char *trimmed = trim(line);
        char **args = parse_args(trimmed);
        run_proc(args);
        free(line);
    }


    return 0;
}