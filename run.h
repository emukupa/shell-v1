#ifndef RUN
#define RUN
#define SHELL_READ_LINE_BUFFER_SIZE 1024
#define SHELL_TOKEN_BUFFER_SIZE 64
#define SHELL_TOKEN_DELIMETER " \t\r\n\a"
#define SHELL_USE_STD_GETLINE // use getline instead of getchar

/*
 * Function declarations for builtin shell comands
 * shell_cd
 * shell_exit
 * shell_help
 * shell_play
 */

int shell_cd(char **args);
int shell_exit(char **args);
int shell_help(char **args);
int shell_play(char **args);

char *read_shell(void);
char **split_line(char *arg);
int execute(char **args);
void run(void);
#endif // !RUN