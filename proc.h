#ifndef PROC_H
#define PROC_H
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
#endif