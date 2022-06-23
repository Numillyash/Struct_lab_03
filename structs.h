#ifndef STRUCTS_H
#define STRUCTS_H

#include "config.h"

#define MAX_EXIST_OBJ 255

static const char right_symb_name[] = " QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiop[]{}asdfghjkl;zxcvbnm,.?!@~`#№_%^&()+-0123456789";
static const char right_symb_ext[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789";

#define extinsion_lenth 10
#define filename_lenth 50
#define creation_time_length 17

typedef struct _File
{
    char creation_time[creation_time_length + 1];
    char creation_date[creation_time_length + 1];
    char filename[filename_lenth + 1];
    char extension[extinsion_lenth + 1];
    struct _Folder *parent;
} File;

int createFile(char *file_name, char *extension, File *file);

typedef struct _Folder
{
    uint16_t files_count_cur;
    uint16_t folders_count_cur;
    uint16_t files_count_max;
    uint16_t folders_count_max;
    uint16_t exists_into;
    char creation_time[creation_time_length + 1];
    char creation_date[creation_time_length + 1];
    char filename[filename_lenth + 1];
    File *files;
    struct _Folder *folders;
    struct _Folder *parent;
} Folder;

int checkFolderExists(char *folder_name, Folder *fld);

int createFolder(char *folder_name, Folder *folder);

int addFolder(char *folder_name, Folder *fld);

int addFile(char *file_name, char *extension, Folder *fld);

int print_list(Folder *fld, int mode);

int save_path(Folder *fld, File *fil, FILE* fp);

int get_path(Folder *fld, File *fil);

void delete_file(File *deleting);

void delete_folder(Folder *deleting);

void find_folder(char *name, Folder *parent);

void find_file(char *name, char *ext, Folder *parent);

#endif