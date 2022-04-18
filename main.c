#include "structs.h"

int main()
{
    File new_file;
    Folder new_folder;
    createFile("huy", "pizda", &new_file);
    createFolder("root", &new_folder);
    printf("%s\n", new_file.creation_time);
    
    printf("%s\n", new_folder.creation_time);
    printf("%s\n", new_folder.filename);
    printf("%d\n", new_folder.folders_count_cur);
    printf("%d\n", new_folder.files_count_cur);
    printf("%d\n", new_folder.files_count_max);
    printf("%d\n", new_folder.folders_count_max);

    printf("%d\n", new_folder.exists_into);



    printf("\n%d\n", addFolder("soso", &new_folder));
    printf("%d\n", new_folder.exists_into);
    printf("%d\n", new_folder.folders_count_cur);
    printf("%d\n", new_folder.files_count_cur);
    printf("%d\n", new_folder.files_count_max);
    printf("%d\n", new_folder.folders_count_max);
    printf("%s\n", new_folder.folders[0].creation_time);
    printf("%s\n", new_folder.folders[0].filename);
    
    
    printf("\n%d\n", addFolder("soso2", &new_folder));
    printf("%d\n", new_folder.exists_into);
    printf("%d\n", new_folder.folders_count_cur);
    printf("%d\n", new_folder.files_count_cur);
    printf("%d\n", new_folder.files_count_max);
    printf("%d\n", new_folder.folders_count_max);
    printf("%s\n", new_folder.folders[1].creation_time);
    printf("%s\n", new_folder.folders[1].filename);

    printf("%-*d%-*d%-*d\n", 10, 1376513765, 10, 123, 10, 1874);

    return SUCCESS;
}

// нужно ли добавить верхнего родителя?
// про одинаковые имена файлов/папок
// ls по алфавиту?