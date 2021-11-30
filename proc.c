#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
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
        if (strchr(trimmed, '|'))
        {
            mypipe(trimmed);
        }
        else if (strstr(trimmed, ">>"))
        {
            redirect_stdout(trimmed, 1);
        }
        else if (strchr(trimmed, '>'))
        {
            redirect_stdout(trimmed, 0);
        }
        else if (strchr(trimmed, '<'))
        {
            redirect_stdin(trimmed);
        }
        else
        {
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
                return -1;
            }
            else
            {
                run_proc(args);
            }
            free(args);
        }
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

void mypipeSupport(FILE *output, char *parse)
{
    char buffer[2056];
    char *bufferP = buffer;
    int i = 0;
    char c;
    while ((buffer[i] = fgetc(output)) != EOF)
    {
        i++;
    }
    buffer[i] = '\0';

    char *new_str;
    if ((new_str = malloc(strlen(parse) + strlen(bufferP) + 1)) != NULL)
    {
        new_str[0] = '\0'; // ensures the memory is an empty string
        strcat(new_str, parse);
        strcat(new_str, bufferP);
    }
    else
    {
        printf("malloc failed!\n");
    }

    printf("command: \t %s \n", new_str);
}

void mypipe(char *input)
{
    char **parsed = parse_pipe(input);

    FILE *output_stream = popen(parsed[0], "r");

    mypipeSupport(output_stream, parsed[0]);

    int counter = 1;
    while (parsed[counter])
    {
        printf("\ninside pipe \n");
        char buffer[2056];
        int i = 0;
        char c;
        while ((buffer[i] = fgetc(output_stream)) != EOF)
        {
            i++;
        }
        buffer[i] = '\0';
        FILE *input_stream = popen(parsed[counter], "w");
        fputs(buffer, input_stream);

        pclose(output_stream);

        //getting output for command if multiple piping is present
        // output_stream = popen(parsed[counter], "r");
        pclose(input_stream);
        counter++;
    }

    // pclose(output_stream);

    free(parsed);
}

void redirect_stdout(char *input, char append)
{
    char **parsed;
    if (append)
    {
        parsed = parse_append_stdout_redirect(input);
    }
    else
    {
        parsed = parse_stdout_redirect(input);
    }
    char *trimmed = trim(parsed[1]);

    int flag = append ? O_APPEND : O_TRUNC;
    int fd = open(trimmed, O_WRONLY | flag, 0644);
    if (fd == -1)
    {
        printf("%s: %s\n", trimmed, strerror(errno));
        return;
    }
    int tmp_stdout = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);

    char **args = parse_args(trim(parsed[0]));
    run_proc(args);

    dup2(tmp_stdout, STDOUT_FILENO);
    free(parsed);
    free(args);
}

void redirect_stdin(char *input)
{
    char **parsed = parse_stdin_redirect(input);
    char *trimmed = trim(parsed[1]);

    int fd = open(trimmed, O_RDONLY);
    if (fd == -1)
    {
        printf("%s: %s\n", trimmed, strerror(errno));
        return;
    }

    int tmp_stdin = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);

    char **args = parse_args(trim(parsed[0]));
    run_proc(args);

    dup2(tmp_stdin, STDIN_FILENO);
    free(parsed);
    free(args);
}