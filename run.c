#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "run.h"

/**
 * @brief List of built in commands, followed by their corresponding functions
 *
 */
char *builtin_str[] = {
    "cd",
    "exit",
    "help",
    "play",
};

int (*builtin_func[])(char **) = {&shell_cd, &shell_exit, &shell_help, &shell_play};

int shell_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

/**
 * @brief forks the main process
 *
 * @param args
 * @return int
 */
int shell_launch(char **args)
{
    pid_t pid = fork();
    int status;

    if (pid == 0)
    {
        // child process
        if (execvp(args[0], args) == -1)
        {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        // error when forking
        perror("shell");
    }
    else
    {
        // parent process
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/**
 * @brief reads the input commands and arguments
 *
 * @return char*
 */
char *read_shell(void)
{
#ifdef SHELL_USE_STD_GETLINE
    char *line = NULL;
    size_t buffer_size = 0; // getline will allocate a buffer for us
    if (getline(&line, &buffer_size, stdin) == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("shell: readline\n");
            exit(EXIT_FAILURE);
        }
    }

    return line;
#else
    int buffer_size = SHELL_READ_LINE_BUFFER_SIZE;
    char *buffer = malloc(sizeof(char) * buffer_size);
    int position = 0;

    if (!buffer)
    {
        fprintf(stderr, "shell: memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // read a character
        int character = getchar();

        // If we hit EOF, replace it wit a null character and return
        if (character == EOF || character == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = character;
        }
        position++;

        // If we have succeeded the buffer,  reallocate memory
        if (position >= buffer_size)
        {
            buffer_size += SHELL_READ_LINE_BUFFER_SIZE;
            buffer = realloc(buffer, buffer_size);
            if (!buffer)
            {
                if (!buffer)
                {
                    fprintf(stderr, "shell: memory re-allocation error\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
#endif
}

/*
 * Builtin function implementations
 */
int shell_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("shell");
        }
    }
    return 1;
}

int shell_exit(char **args)
{
    printf("The argument size is %ld\n", sizeof args);
    if (sizeof args == 0)
    {
        return 0;
    }
    return 1;
}

int shell_help(char **args)
{
    printf("The argument size is %ld\n", sizeof args);
    printf("Edward Manda's Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < shell_num_builtins(); i++)
    {
        printf(" %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int shell_play(char **args)
{
    printf("The argument size is %ld\n", sizeof args);
    puts("This is just for fun.....");
    return 1;
}

/**
 * @brief receives a string of commands and arguments and splits them
 *
 * @param arg
 * @return char**
 */
char **split_line(char *arg)
{
    int buffer_size = SHELL_TOKEN_BUFFER_SIZE;
    int position = 0;
    char **tokens = malloc(buffer_size * sizeof(char));

    // grab the firt argument
    char *token = strtok(arg, SHELL_TOKEN_DELIMETER);

    // loop over the arguments
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        // check if we has reached buffer size, allocate more memory
        if (position >= buffer_size)
        {
            buffer_size += SHELL_TOKEN_BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size * sizeof(char));
            if (!tokens)
            {
                fprintf(stderr, "shell: memory re-allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, SHELL_TOKEN_DELIMETER);
    }
    tokens[position] = NULL;

    return tokens;
}

int execute(char **args)
{
    if (args[0] == NULL)
    {
        // no command was entered
        return 1;
    }

    for (int i = 0; i < shell_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }

    return shell_launch(args);
}

void run()
{
    char *line;
    char **args;
    int status;

    // loop until status exits
    do
    {
        printf("> ");
        /**
         * @brief Read:
         * Read the command from standard input.
         */
        line = read_shell();

        /**
         * @brief Parse:
         * Separate the command string into a program and arguments.
         */
        args = split_line(line);

        /**
         * @brief Execute:
         * Run the parsed command.
         */
        status = execute(args);
        printf("here %d", status);

        // free memory
        free(line);
        free(args);
    } while (status);
}