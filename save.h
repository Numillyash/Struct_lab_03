#include "include/ui.h"
#include <stdio.h>
#include "structs.h"

#define SAVEFILENAME "save.dat"

FILE *SAVE;

int newRecord(char *time, char *date, Folder *folder, char *command)
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