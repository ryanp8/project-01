#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#include "util.h"
#include "proc.h"
#include "input.h"

int run(char *input)
{
    char **commands = parse_commands(input);
    int i = 0;
    while (commands[i])
    {
        char *trimmed = trim(commands[i]);

        printf("trimed ->%s\n", trimmed);

        //check if there are any piping
        char *pipePosition = strchr(trimmed, '|');

        if (pipePosition)
        {
            printf("pipe detected");
        }
        char **args = parse_args(trimmed);
        if (strcmp(args[0], "cd") == 0)
        {
            if (args[1])
            {
                if (cd(args[1]) == -1)
                {
                    printf("Error %d: %s\n", errno, strerror(errno));
                }
            }
            else
            {
                cd("~");
            }
        }
        else if (strcmp(args[0], "exit") == 0)
        {
            free(input);
            free(args);
            free(commands);
            return -1;
        }
        else
        {
            run_proc(args);
        }
        free(args);
        i++;
    }
    free(commands);
    return 0;
}

void run_proc(char **args)
{
    int f = fork();
    if (f)
    {
        int w, status;
        w = waitpid(f, &status, 0);
    }
    else
    {
        int res = execvp(args[0], args);
        if (res == -1)
        {
            printf("command not found: %s\n", args[0]);
            kill(getpid(), 2);
        }
    }
}

int cd(char *path)
{
    char cwd[MAX_PATH_LEN];
    if (strcmp(path, "~") == 0)
    {
        while (charcount(getcwd(cwd, sizeof(cwd)), '/') > 2)
        {
            if (chdir("..") == -1)
            {
                return -1;
            }
        }
        return 0;
    }
    else
    {
        return chdir(path);
    }
}