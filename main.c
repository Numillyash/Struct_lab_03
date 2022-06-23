#include <stdio.h>

// #include "structs.h"

#include "handler.h"

int main(int argc, char **argv)
{
    Folder *CurrentFolder;
    Folder *RootFolder;

    createFolder("root", RootFolder);
    CurrentFolder = RootFolder;

    int iResult;
    char *buf;

    printf("bruh1\n");
    readRecords(&RootFolder);
    printf("bruh2\n");

    while (1)
    {
        printf("%s > ", CurrentFolder->filename);
        buf = commandCallHandler();

        if (buf == NULL)
        {
            printf("Input too long!\n");
        }

        iResult = commandParserHandler(buf, RootFolder, &CurrentFolder);
        printf("result: %d\n", iResult);
    }

    return 0;
}