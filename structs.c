#include "structs.h"

int check_name(char *name)
{
    int strln = strlen(name);
    int i;
    char *symb;

    if (strln > filename_lenth)
        return FILENAME_LENGTH_FAILURE;

    for (i = 0; i < strln; i++)
    {
        symb = strchr(right_symb_name, name[i]);
        if (symb == 0)
            return FILENAME_SYMBOL_FAILURE;
    }

    if (name[strln - 1] == '.')
        return FILENAME_ENDING_FAILURE;

    return SUCCESS;
}

int check_ext(char *ext)
{
    int strln = strlen(ext);
    int i;
    char *symb;

    if (strln > extinsion_lenth)
        return FILENAME_LENGTH_FAILURE;

    for (i = 0; i < strln; i++)
    {
        symb = strchr(right_symb_ext, ext[i]);
        if (symb == 0)
            return FILENAME_SYMBOL_FAILURE;
    }

    if (ext[strln - 1] == '.')
        return FILENAME_ENDING_FAILURE;

    return SUCCESS;
}

int createFile(char *file_name, char *extension, File *file)
{
    ERROR_CODE errno;
    time_t time_now;
    struct tm *time_info;
    File result = {"\0", "\0", "\0"};

    time(&time_now);
    time_info = localtime(&time_now);

    strftime(result.creation_time, creation_time_length, "%T %D", time_info);
    strftime(result.creation_date, creation_time_length, "%D ", time_info);

    if ((errno = check_name(file_name)) != SUCCESS)
        return errno;

    if ((errno = check_ext(extension)) != SUCCESS)
        return errno;

    strcpy(result.filename, file_name);

    strcpy(result.extension, extension);

    *file = result;

    return SUCCESS;
}

int createFolder(char *folder_name, Folder *folder)
{
    ERROR_CODE errno;
    time_t time_now;
    struct tm *time_info;
    Folder result = {0, 0, 1, 1, 0, "\0", "\0"};

    if ((errno = check_name(folder_name)) != SUCCESS)
        return errno;

    strcpy(result.filename, folder_name);

    time(&time_now);
    time_info = localtime(&time_now);

    strftime(result.creation_time, creation_time_length, "%T %D", time_info);
    strftime(result.creation_date, creation_time_length, "%D ", time_info);

    result.files = (File *)malloc(sizeof(File));
    result.folders = (Folder *)malloc(sizeof(Folder));

    if (result.files == NULL || result.folders == NULL)
        return MEMORY_ALLOCATION_FAILURE;

    *folder = result;

    return SUCCESS;
}

int addFolder(char *folder_name, Folder *fld)
{
    if (fld->exists_into < MAX_EXIST_OBJ)
    {
        int errno, i;
        Folder newFolder;
        Folder *buffer;

        for (i = 0; i < fld->folders_count_cur; i++)
        {
            if (!strcmp(folder_name, fld->folders[i].filename))
                return EXISTING_NAME_FAILURE;
        }

        errno = createFolder(folder_name, &newFolder);
        if (errno != SUCCESS)
            return errno;

        fld->folders[fld->folders_count_cur] = newFolder;
        fld->exists_into++;
        fld->folders_count_cur++;

        if (fld->folders_count_cur == fld->folders_count_max)
        {
            fld->folders_count_max <<= 1;
            buffer = (Folder *)malloc(sizeof(Folder) * (fld->folders_count_cur));
            if (buffer == NULL)
                return MEMORY_ALLOCATION_FAILURE;
            for (i = 0; i < fld->folders_count_cur; ++i)
            {
                buffer[i] = fld->folders[i];
            }
            free(fld->folders);
            fld->folders = (Folder *)malloc(sizeof(Folder) * (fld->folders_count_max));
            if (fld->folders == NULL)
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
}

int addFile(char *file_name, char *extension, Folder *fld)
{
    if (fld->exists_into < MAX_EXIST_OBJ)
    {
        int errno, i;
        File newFile;
        File *buffer;

        for (i = 0; i < fld->files_count_cur; i++)
        {
            if (!strcmp(extension, fld->files[i].extension) && !strcmp(file_name, fld->files[i].filename))
                return EXISTING_NAME_FAILURE;
        }

        errno = createFile(file_name, extension, &newFile);
        if (errno != SUCCESS)
            return errno;

        fld->files[fld->files_count_cur] = newFile;
        fld->exists_into++;
        fld->files_count_cur++;

        if (fld->files_count_cur == fld->files_count_max)
        {
            fld->files_count_max <<= 1;
            buffer = (File *)malloc(sizeof(File) * (fld->files_count_cur));
            if (buffer == NULL)
                return MEMORY_ALLOCATION_FAILURE;
            for (i = 0; i < fld->files_count_cur; ++i)
            {
                buffer[i] = fld->files[i];
            }
            free(fld->files);
            fld->files = (File *)malloc(sizeof(File) * (fld->files_count_max));
            if (fld->files == NULL)
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
}

int print_list(Folder *fld, int mode)
{
    int i; // iterator

    if (mode == 0) // simple
    {
        printf("Files:\n");
        for (i = 0; i < fld->files_count_cur; i++)
            printf("%*s.%-*s\n", filename_lenth, fld->files[i].filename, extinsion_lenth, fld->files[i].extension);
        printf("Folders:\n");
        for (i = 0; i < fld->folders_count_cur; i++)
            printf("%*s\n", filename_lenth, fld->folders[i].filename);
    }
    if (mode == 1) // not simple
    {
        printf("┌─────────────────────┬────────────────────────────────────────────────────┐\n");
        printf("│    Current folder   │ %*s │\n", filename_lenth, fld->filename);
        printf("├──────────┬──────────┼────────────────────────────────────────────────────┼────────────┐\n");
        printf("│   Time   │   Date   │                     Filenames                      │  Extension │\n");
        printf("├──────────┼──────────┼────────────────────────────────────────────────────┼────────────┤\n");

        for (i = 0; i < fld->files_count_cur; i++)
            printf("│ %s│ %s│ %*s │ %*s │\n", fld->files[i].creation_time, fld->files[i].creation_date, filename_lenth, fld->files[i].filename, extinsion_lenth, fld->files[i].extension);
        printf("├──────────┼──────────┼────────────────────────────────────────────────────┼────────────┘\n");
        printf("│   Time   │   Date   │                     Foldernames                    │\n");
        printf("├──────────┼──────────┼────────────────────────────────────────────────────┤\n");
        for (i = 0; i < fld->folders_count_cur; i++)
            printf("│ %s│ %s│ %*s │\n", fld->folders[i].creation_time, fld->folders[i].creation_date, filename_lenth, fld->folders[i].filename);
        printf("└──────────┴──────────┴────────────────────────────────────────────────────┘\n");
    }
}
