#ifndef INPUT_H
#define INPUT_H
char *readln();
char **parse_args(char *input);
char **parse_commands(char *input);
char **parse_pipe(char *input);
char **parse_redirect(char *input);
#endif