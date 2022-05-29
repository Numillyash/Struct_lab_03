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

int createFile(char* file_name, char* extension, File* file)
{
    ERROR_CODE errno;
    time_t time_now;
    struct tm* time_info;
    File result = {"\0","\0","\0"};

    time(&time_now);
    time_info = localtime(&time_now);

    strftime (result.creation_time,creation_time_length,"%T %D",time_info);

    if((errno = check_name(file_name)) != SUCCESS)
        return errno;
    
    strcpy(result.filename, file_name);

    strcpy(result.extension, extension);

    *file = result;
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
    int errno, i;
    Folder newFolder;
    Folder* buffer;

    errno = createFolder(folder_name, &newFolder);
    if(errno != SUCCESS)
        return errno;
    
    fld->folders[fld->folders_count_cur] = newFolder;
    fld->exists_into++;
    fld->folders_count_cur++;

    if(fld->folders_count_cur == fld->folders_count_max)
    {
        fld->folders_count_max <<= 1;
        buffer = (Folder*)malloc(sizeof(Folder) * (fld->folders_count_cur));
        if(buffer == NULL)
            return MEMORY_ALLOCATION_FAILURE;
        for (i = 0; i < fld->folders_count_cur; ++i)
		{
			buffer[i] = fld->folders[i];
		}
        free(fld->folders);
        fld->folders = (Folder*)malloc(sizeof(Folder) * (fld->folders_count_max));
        if(fld->folders == NULL)
            return MEMORY_ALLOCATION_FAILURE;
        for (i = 0; i < fld->folders_count_cur; ++i)
		{
			fld->folders[i] = buffer[i];
		}
        free(buffer);
    }

    fld->folders[fld->folders_count_cur].parent = fld;

    return SUCCESS;
}

int addFile(char* file_name, char* extension, Folder* fld)
{
    int errno, i;
    File newFile;
    File* buffer;

    errno = createFile(file_name, extension, &newFile);
    if(errno != SUCCESS)
        return errno;
    
    fld->files[fld->files_count_cur] = newFile;
    fld->exists_into++;
    fld->files_count_cur++;

    if(fld->files_count_cur == fld->files_count_max)
    {
        fld->files_count_max <<= 1;
        buffer = (File*)malloc(sizeof(File) * (fld->files_count_cur));
        if(buffer == NULL)
            return MEMORY_ALLOCATION_FAILURE;
        for (i = 0; i < fld->files_count_cur; ++i)
		{
			buffer[i] = fld->files[i];
		}
        free(fld->files);
        fld->files = (File*)malloc(sizeof(File) * (fld->files_count_max));
        if(fld->files == NULL)
            return MEMORY_ALLOCATION_FAILURE;
        for (i = 0; i < fld->files_count_cur; ++i)
		{
			fld->files[i] = buffer[i];
		}
        free(buffer);
    }

    fld->files[fld->files_count_cur].parent = fld;

    return SUCCESS;
}

int print_list(Folder* fld)
{
    
}
