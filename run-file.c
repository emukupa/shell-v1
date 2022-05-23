#include <stdlib.h>
#include <stdio.h>
#include "run-file.h"

void run_file(const char *filename)
{
    FILE *fp = fopen(filename, "r"); // read mode
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    // TODO run the commands from the file
    printf("The contents of %s file are:\n", filename);
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(fp);
}