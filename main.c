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
    }

    return 0;
}