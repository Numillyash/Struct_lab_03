#include <stdio.h>

#include "structs.h"
#include "include/ui.h"
#include "handler.h"

int main(int argc, char** argv)
{
    int iResult;
    char* buf;
    
    while (1)
    {
        printf("> ");
        buf = commandCallHandler();

        if (buf == NULL)
        {
            printf("Input too long!\n");
        }

        iResult = commandParserHandler(buf);
        printf("result: %d\n", iResult);
    }

    return 0;
}