#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#include "input.h"
#include "util.h"


void print_prompt() {
    printf("\x1b[35m$\x1b[0m ");
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
        if (strlen(trimmed) > 1) {
            char **args = parse_args(trimmed);
            int res = run_proc(args);
            if (res == -1) {
                printf("Errno: %d, %s\n", errno, strerror(errno));
            }
        }
        free(line);
    }


    return 0;
}