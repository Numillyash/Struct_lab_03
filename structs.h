#include "config.h"

#define extinsion_lenth 5
#define filename_lenth 10
#define creation_time_length 17


typedef struct
{
    char creation_time[creation_time_length+1];
    char filename[filename_lenth+1];
    char extension[extinsion_lenth+1];
}File;

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