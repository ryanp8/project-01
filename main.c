#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "input.h"
#include "proc.h"
#include "util.h"


void print_prompt() {
    char cwd[MAX_PATH_LEN] = {0};
    char *p = getcwd(cwd, sizeof(cwd));
    if (charcount(p, '/') > 1) {
        p[strlen(p)] = '/';

        strsep(&p, "/");
        strsep(&p, "/");

        while ((*p) != '/') {
            p++;
        }
        *--p = '~';
    }
    printf("\x1b[32m%s \x1b[36m:: ", p);
    printf("\x1b[35m$\x1b[0m ");
}

int main() {

    cd("~");

    while (1) {
        print_prompt();
        char *line = readln();
        char *trimmed = trim(line);
        if (strlen(trimmed) > 0) {
            char **args = parse_args(trimmed);
            int res;
            if (strcmp(args[0], "cd") == 0) {
                if (args[1]) {
                    res = cd(args[1]);
                }
                else {
                    cd("~");
                }
            }
            else if (strcmp(args[0], "exit") == 0) {
                free(line);
                free(args);
                break;
            }
            else {
                res = run_proc(args);
            }
            if (res == -1) {
                printf("Error %d: %s\n", errno, strerror(errno));
            }
            free(args);
        }
        free(line);
    }


    return 0;
}