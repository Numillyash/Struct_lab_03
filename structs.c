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

int checkFolderExists(char *folder_name, Folder *fld)
{
    int i;
    for (i = 0; i < fld->folders_count_cur; i++)
    {
        if (!strcmp(folder_name, fld->folders[i].filename))
            return EXISTING_NAME_FAILURE;
    }
    return SUCCESS;
}

int checkFileExists(char *file_name, char *extension, Folder *fld)
{
    int i;
    for (i = 0; i < fld->files_count_cur; i++)
    {
        if (!strcmp(extension, fld->files[i].extension) && !strcmp(file_name, fld->files[i].filename))
            return EXISTING_NAME_FAILURE;
    }
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

    strftime(result.creation_time, creation_time_length, "%T", time_info);
    strftime(result.creation_date, creation_time_length, "%D", time_info);

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

    strftime(result.creation_time, creation_time_length, "%T", time_info);
    strftime(result.creation_date, creation_time_length, "%D", time_info);

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

        if (checkFolderExists(folder_name, fld)) // если папки не существует...
        {
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

        fld->folders[fld->folders_count_cur - 1].parent = fld;

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

        if (checkFileExists(file_name, extension, fld))
        {
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

        fld->files[fld->files_count_cur - 1].parent = fld;

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
            printf("│ %s │ %s │ %*s │ %*s │\n", fld->files[i].creation_time, fld->files[i].creation_date, filename_lenth, fld->files[i].filename, extinsion_lenth, fld->files[i].extension);
        printf("├──────────┼──────────┼────────────────────────────────────────────────────┼────────────┘\n");
        printf("│   Time   │   Date   │                     Foldernames                    │\n");
        printf("├──────────┼──────────┼────────────────────────────────────────────────────┤\n");
        for (i = 0; i < fld->folders_count_cur; i++)
            printf("│ %s │ %s │ %*s │\n", fld->folders[i].creation_time, fld->folders[i].creation_date, filename_lenth, fld->folders[i].filename);
        printf("└──────────┴──────────┴────────────────────────────────────────────────────┘\n");
    }
}

void delete_file(File *deleting)
{
    int i; // iterator
    int file_ind = -1;
    if (deleting != NULL)
    {
        Folder *parent = deleting->parent;

        for (i = 0; i < parent->files_count_cur; i++)
        {
            if (&(parent->files[i]) == deleting)
                file_ind = i;
        }

        for (i = file_ind; i < parent->files_count_cur; i++)
        {
            parent->files[i] = parent->files[i + 1];
        }
        parent->files_count_cur--;
    }
}

void delete_folder(Folder *deleting)
{
    // char *p = (char *)malloc(1);
    // p[0] = '\0';
    // get_path(p, deleting, NULL);
    //  printf("%d\n", deleting->folders_count_cur);
    //  printf("%d\n", deleting->parent->folders_count_cur);

    // print_list(deleting, 1);
    int i; // iterator
    int fold_ind = -1;
    if (deleting != NULL)
    {
        Folder *parent = deleting->parent;

        for (i = 0; i < parent->folders_count_cur; i++)
        {
            if (&(parent->folders[i]) == deleting)
                fold_ind = i;
        }

        printf("%d\n", fold_ind);

        free(deleting->files);
        while (deleting->folders_count_cur)
        {
            delete_folder(&(deleting->folders[deleting->folders_count_cur - 1]));
        }
        free(deleting->folders);

        for (i = fold_ind; i < parent->folders_count_cur; i++)
        {
            parent->folders[i] = parent->folders[i + 1];
        }
        parent->folders_count_cur--;
    }
    // print_list(deleting->parent, 1);
}

int save_path(Folder *fld, File *fil, FILE *fp)
{
    Folder *parent;
    if (fld != NULL)
    {
        parent = fld->parent;
    }
    else if (fil != NULL)
    {
        parent = fil->parent;
    }
    else
    {
        return 0;
    }

    if (parent != NULL)
    {
        save_path(parent, NULL, fp);
        if (fld != NULL)
        {
            fprintf(fp, "/%s", fld->filename);
        }
        else if (fil != NULL)
        {
            fprintf(fp, "/%s.%s", fil->filename, fil->extension);
        }
    }
    else
    {
    }

    return 1;
}

int get_path(Folder *fld, File *fil)
{
    Folder *parent;

    if (fld != NULL)
    {
        parent = fld->parent;
    }
    else if (fil != NULL)
    {
        parent = fil->parent;
    }
    else
    {
        return 0;
    }

    if (parent != NULL)
    {
        get_path(parent, NULL);
        if (fld != NULL)
        {
            printf("/%s", fld->filename);
        }
        else if (fil != NULL)
        {
            parent = fil->parent;
            printf("/%s.%s", fil->filename, fil->extension);
        }
    }
    else
    {
        printf("/%s", fld->filename);
    }

    return 1;
}

void find_folder(char *name, Folder *parent)
{
    int i = 0;
    char *path;
    // print_list(parent, 1);
    for (i = 0; i < parent->folders_count_cur; i++)
    {
        // printf("Im in %s\n", parent->folders[i].filename);

        if (!strcmp(name, parent->folders[i].filename))
        {
            get_path(&(parent->folders[i]), NULL);
            printf("\n");
        }
        find_folder(name, &(parent->folders[i]));
    }
}

void find_file(char *name, char *ext, Folder *parent)
{
    char *path;
    int i = 0;
    for (i = 0; i < parent->files_count_cur; i++)
    {
        if (!strcmp(name, parent->files[i].filename) && !strcmp(ext, parent->files[i].extension))
        {
            get_path(NULL, &(parent->files[i]));
            printf("\n");
        }
    }
    for (i = 0; i < parent->folders_count_cur; i++)
    {
        find_file(name, ext, &(parent->folders[i]));
    }
}