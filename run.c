#include <stdio.h>
#include <stdlib.h>
#include "run.h"

char *read_shell(void)
{
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
    puts("read");
    return line;
}

void run()
{
    char *line;
    // char **args;
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
        // args = split_line(line);
        // printf("First argument is %s", args[0]);

        /**
         * @brief Execute:
         * Run the parsed command.
         */
        status = 0;
    } while (status);
}