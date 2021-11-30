# project-01

Our shell implements command execution (multiple can be run using semicolons), single piping, single redirections (using >, <, and >>). Any number of spaces can be put between dividing characters.
The prompt displays the current working directory

## Function headers
```C
int run(char *input);
void run_proc(char **args);
int cd(char *dir);
void exit();
void mypipe(char *input);
void swap_filetable(int fd1, int fd2);
void redirect_stdout(char *input, char append);  
void redirect_stdin(char *input); 
void redirect_append_stdout(char *input);  
void redirect_append_stdin(char *input);

char *readln();
char **parse_args(char *input);
char **parse_commands(char *input);
char **parse_pipe(char *input);
char **parse_stdout_redirect(char *input);
char **parse_stdin_redirect(char *input);
char **parse_append_stdout_redirect(char *input);

char *trim(char *line);
int charcount(char *line, char c);
int substrcount(char *line, char *substr);
char **split(char *input, char* tok);
void print_prompt();
```
