#include "structs.h"

int main()
{
    File new_file = createFile();
    Folder new_folder;
    createFolder("idi nahuy", &new_folder);
    printf("%s\n", new_file.creation_time);
    
    printf("%s\n", new_folder.creation_time);
    printf("%s\n", new_folder.filename);
    printf("%d\n", new_folder.folders_count_cur);
    printf("%d\n", new_folder.files_count_cur);
    printf("%d\n", new_folder.files_count_max);
    printf("%d\n", new_folder.folders_count_max);

    printf("%d\n", new_folder.exists_into);



    printf("%d\n", addFolder("soso", &new_folder));
    printf("%d\n", new_folder.exists_into);
    printf("%s\n", new_folder.folders[0].creation_time);
    printf("%s\n", new_folder.folders[0].filename);
    
    return 0;
}

// нужно ли добавить верхнего родителя?