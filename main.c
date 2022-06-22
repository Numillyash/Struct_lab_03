#include <stdio.h>

// #include "structs.h"
#include "include/ui.h"
#include "handler.h"

int main(int argc, char** argv)
{
    Folder* CurrentFolder;
    Folder RootFolder;

    createFolder("root", &RootFolder);
    CurrentFolder = &RootFolder;

    int iResult;

    addFolder("test1", &RootFolder);
    addFolder("test2", &RootFolder);
    addFolder("test3", &RootFolder);

    addFolder("test11", &RootFolder.folders[0]);

    // Folder* ResultFolder = NULL;
    // File* ResultFile = NULL;

    // printf("!!! %d\n", &RootFolder.folders[0]);

    // iResult = checkArgumentValid("ls", "/test1/", &RootFolder, CurrentFolder, &ResultFolder, &ResultFile);
    // // iResult = checkMajorArgumenntValid("/", &RootFolder, CurrentFolder, &ResultFolder, &ResultFile);
    // printf("%d\n", iResult);

    // if (ResultFolder != NULL)
    // {
    //     printf("%s\n", ResultFolder->filename);
    //     print_list(ResultFolder, 0);
    // }

    // else
    //     printf("ResultFolder is NULL\n");

    char* buf;
    
    while (1)
    {
        printf("%s > ", CurrentFolder->filename);
        buf = commandCallHandler();

        if (buf == NULL)
        {
            printf("Input too long!\n");
        }

        iResult = commandParserHandler(buf, &RootFolder, &CurrentFolder);
        printf("result: %d\n", iResult);
    }

    return 0;
}