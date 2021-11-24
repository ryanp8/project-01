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
    printf("MYSH \x1b[35m:: \x1b[32m%s \x1b[36m$\x1b[0m ", p);
}

int main() {

    cd("~");

    while (1) {
        print_prompt();
        char *line = readln();
        char *trimmed = trim(line);
        if (run(trimmed) == -1) {
            break;
        }
        free(line);
    }


    return 0;
}