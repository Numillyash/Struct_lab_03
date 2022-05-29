#ifndef STRUCTS_H
#define STRUCTS_H

#include "config.h"

static const char right_symb[] = " qwertyuiop[]{}asdfghjkl;zxcvbnm,.?!@~`#№$%^&()+-0123456789";

#define extinsion_lenth 10
#define filename_lenth 50
#define creation_time_length 17

typedef struct _File{
    char creation_time[creation_time_length+1];
    char filename[filename_lenth+1];
    char extension[extinsion_lenth+1];
    struct _Folder* parent;
}File;

int createFile(char* file_name, char* extension, File* file);

typedef struct _Folder{
    uint8_t files_count_cur;
    uint8_t folders_count_cur;
    uint8_t files_count_max;
    uint8_t folders_count_max;
    uint8_t exists_into;
    char creation_time[creation_time_length+1];
    char filename[filename_lenth+1];
    File* files;
    struct _Folder* folders;
    struct _Folder* parent;
}Folder;

int createFolder(char* folder_name, Folder* folder);

int addFolder(char* folder_name, Folder* fld);

int addFile(char* file_name, char* extension, Folder* fld);

#endif