#ifndef INPUT_H
#define INPUT_H
char *readln();
char **parse_args(char *input);
char **parse_commands(char *input);
char **parse_pipe(char *input);
char **parse_stdout_redirect(char *input);
char **parse_stdin_redirect(char *input);
char **parse_append_stdout_redirect(char *input);
#endif