#include "structs.h"

int check_name(char* name)
{
    int strln = strlen(name);
    int i;
    char* symb;

    if(strln > filename_lenth)
        return FILENAME_LENGTH_FAILURE;
    
    for(i = 0; i < strln; i ++)
    {
        symb = strchr(right_symb, name[i]);
        if(symb == 0)
            return FILENAME_SYMBOL_FAILURE;
    }

    if(name[strln-1] == '.')
        return FILENAME_ENDING_FAILURE;

    return SUCCESS;
}

File createFile()
{
    time_t time_now;
    struct tm* time_info;
    File result = {"\0","\0","\0"};

    time(&time_now);
    time_info = localtime(&time_now);

    strftime (result.creation_time,creation_time_length,"%T %D",time_info);

    return result;
}

int createFolder(char* folder_name, Folder* folder)
{
    ERROR_CODE errno;
    time_t time_now;
    struct tm* time_info;
    Folder result = {0, 0, 1, 1, 0, "\0","\0"};
    
    if((errno = check_name(folder_name)) != SUCCESS)
        return errno;
    
    strcpy(result.filename, folder_name);

    time(&time_now);
    time_info = localtime(&time_now);

    strftime (result.creation_time,creation_time_length,"%T %D",time_info);

    result.files = (File*) malloc(sizeof(File));
    result.folders = (Folder*) malloc(sizeof(Folder));

    if(result.files == NULL || result.folders == NULL)
        return MEMORY_ALLOCATION_FAILURE;

    *folder = result;

    return SUCCESS;
}

int addFolder(char* folder_name, Folder* fld)
{
    int errno;
    Folder newFolder;
    
    errno = createFolder(folder_name, &newFolder);
    if(errno != SUCCESS)
        return errno;
    
    fld->folders[fld->folders_count_cur] = newFolder;
    fld->exists_into++;
    fld->folders_count_cur++;

    return SUCCESS;
}