#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "input.h"
#include "proc.h"
#include "util.h"

// some test cases:
//                       ps                                                   ;                                              pwd              ; ls         ;       whoami
//                       ps                                                   ;                                              pwd              ; ls -a -l -G       ;       whoami
// ps;pwd;ls;whoami


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
    printf("MYSH \x1b[35m:: \x1b[32m%s \x1b[0m\n", p);
}

int main() {

    // cd("~");

    while (1) {
        print_prompt();
        char *line = readln();
        if (!line) {
            break;
        }
        if (strlen(line) > 1) { // greater than 1 to account for automatic newline in stdin
            if (run(line) == -1) {
                break;
            }
        }
        free(line);
        // sleep(1);
    }

    return 0;
}