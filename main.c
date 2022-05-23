
#include <stdlib.h>
#include "init.h"
#include "run.h"
#include "clean.h"

int main(int argc, char const *argv[])
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

    return EXIT_SUCCESS;
}
