#include "structs.h"
#include <stdlib.h>

int main()
{
    int i;
    File new_file;
    Folder new_folder;
    createFolder("root", &new_folder);
    printf("\n%d\n", addFolder("sos", &new_folder));
    /*printf("%d\n", new_folder.exists_into);
    printf("%d\n", new_folder.folders_count_cur);
    printf("%d\n", new_folder.files_count_cur);
    printf("%d\n", new_folder.files_count_max);
    printf("%d\n", new_folder.folders_count_max);
    printf("%s\n", new_folder.folders[0].creation_time);
    printf("%s\n", new_folder.folders[0].filename);
    */

    printf("\n%d\n", addFolder("sos2", &new_folder));
    // printf("%d\n", new_folder.exists_into);
    // printf("%d\n", new_folder.folders_count_cur);
    // printf("%d\n", new_folder.files_count_cur);
    // printf("%d\n", new_folder.files_count_max);
    // printf("%d\n", new_folder.folders_count_max);
    printf("%s\n", new_folder.folders[1].creation_time);
    // printf("%s\n", new_folder.folders[1].filename);

    // char name[10];
    // for (i = 0; i < 400; i++)
    // {
    //     sprintf(name, "%d", i);
    //     if (i % 2)
    //     {
    //         printf("\ni = %d : %d\n", i, addFile(name, "test", &new_folder));
    //     }
    //     else
    //     {
    //         printf("\ni = %d : %d\n", i, addFolder(name, &new_folder));
    //     }
    //     printf("%d\n", new_folder.exists_into);
    //     printf("%d\n", new_folder.folders_count_cur);
    //     printf("%d\n", new_folder.folders_count_max);
    //     printf("%d\n", new_folder.files_count_cur);
    //     printf("%d\n", new_folder.files_count_max);
    // }

    addFile("file1", "hehe", &new_folder);
    addFile("file1", "hehe", &new_folder);
    addFile("file1", "huh", &new_folder);
    addFile("trash", "hehe", &new_folder);
    addFile("AvadaBlyad Kedavra", "huy", &new_folder);
    addFile("Ya v svoyom poznanii nastolko preispolnilsya", "budtobi3", &new_folder);
    addFolder("Uh suka so smislam", &new_folder);
    addFolder("Ya v svoyom poznanii nastolko preispolnilsya", &new_folder);
    addFolder("Ya v svoyom poznanii nastolko preispolnilsya", &new_folder);

    // printf("%-*d%-*d%-*d\n", 10, 1376513765, 10, 123, 10, 1874);

    print_list(&new_folder, 1);

    return SUCCESS;
}

// нужно ли добавить верхнего родителя? (да)
// про одинаковые имена файлов/папок (да)
// ls по алфавиту? (нет)
// Дата - название - расширение (табличка)