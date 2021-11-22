#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "util.h"
#include "proc.h"


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

int cd(char *path) {
    char cwd[MAX_PATH_LEN];
    if (strcmp(path, "~") == 0) {
        while (charcount(getcwd(cwd, sizeof(cwd)), '/') > 2) {
            if (chdir("..") == -1) {
                return -1;
            }
        }
        return 0;
    }
    else {
        return chdir(path);
    }
}