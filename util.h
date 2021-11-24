#ifndef UTIL_H
#define UTIL_H
#define MAX_PATH_LEN 256
char *trim(char *line);
int charcount(char *line, char c);
char **split(char *input, char tok);
#endif