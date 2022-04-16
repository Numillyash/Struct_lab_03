#include "structs.h"

int main()
{
    File new_file = createFile();
    printf("%s\n", new_file.creation_time);
    return 0;
}