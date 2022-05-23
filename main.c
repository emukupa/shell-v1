/**
 * @file         main.c
 * @author       Edward Manda
 * @date         May 2022
 * @brief        Shell
 **/

#include <stdlib.h>
#include <stdio.h>
#include "init.h"
#include "run.h"
#include "clean.h"
#include "run-file.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {

        /**
         * @brief Initialize:
         * read and execute the shell configuration files
         */

        init();

        /**
         * @brief Interpret:
         * the shell reads commands from stdin (which could be interactive, or a file) and executes them.
         */
        run();

        /**
         * @brief Terminate:
         * after the commands are executed, the shell executes any shutdown commands, frees up any memory, and terminates.
         */
        clean();
    }
    else
    {
        run_file(argv[1]);
    }

    return EXIT_SUCCESS;
}
