#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **parse_args(char *line) {
    int spaces = 0;
    int j;
    int len = strlen(line);
    for (j = 0; j < len; j++) {
        if (line[j] == ' ') {
            spaces++;
        }
    }
    // char **args = calloc(spaces + 1, sizeof(char*));
    // char **args = malloc(spaces + 1);
    char **args = malloc(5);
    
    char *token;
    int i = 0;
    while (line) {
        token = strsep(&line, " ");
        args[i] = token;
        i++;
    }
    return args;
}

int main() {
    char line[100] = "ls -a -l -i ";

    char ** args = parse_args( line );
    execvp(args[0], args);
    free(args);

    return 0;
}