#include <stdio.h>

#include "structs.h"
#include "include/ui.h"

int main(int argc, char** argv)
{
    char* buf;
    
    while (1)
    {
        buf = commandCallHandler();

        if (buf == 0)
        {
            printf("Unknown Command!");
        }

        
    }

    return 0;
}