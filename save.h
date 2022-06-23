#include "include/ui.h"
#include <stdio.h>
#include "structs.h"

#define SAVEFILENAME "save.dat"

FILE* SAVE;

int newRecord(char* time, char* date, Folder* folder, char* command)
{
    SAVE = fopen(SAVEFILENAME, "a");

    if (SAVE == NULL)
    {
        printf("Unable to open %s\n", SAVEFILENAME);
    }

    if (time != NULL)
    {
        fprintf(SAVE, "%s$%s$", time, date);
    }

    save_path(folder, NULL, SAVE);
    fprintf(SAVE, "$%s", command);

    fclose(SAVE);
}

int readRecords(Folder* RootFolder)
{
    SAVE = fopen(SAVEFILENAME, "r");
    char buf[1000];
    buf[0] = '\0';

    char* sep = "$";

    if (SAVE == NULL)
    {
        printf("Unable to open %s\n", SAVEFILENAME);
    }

    Folder* CurrentFolder;

    while(buf[0] != EOF)
    {
        fscanf(SAVE, "%s", buf);
        char* istr = strtok(buf, sep);
        int i = 0;

        char* time = (char*) malloc(9);
        char* date = (char*) malloc(9);

        while (istr != NULL)
        {
            switch (i)
            {
            case 0:
                strcpy(date, istr);
                break;
            
            case 1:
                strcpy(time, istr);

            case 2:


            default:
                break;
            }
              
            istr = strtok(NULL, sep);
            i++;
        }

        free(time);
        free(date);
    }
}