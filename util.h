#ifndef UTIL_H
#define UTIL_H
#define MAX_PATH_LEN 256
char *trim(char *line);
int charcount(char *line, char c);
int substrcount(char *line, char *substr);
char **split(char *input, char* tok);
void print_prompt();
#endif