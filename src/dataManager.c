#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "../headers/dataManager.h"

int char_is_digit(char character){
    if(character < '0' || character > '9'){
        return 0;
    }
    return 1;
}

int str_is_digit(char *str){
    int i = 0;

    while(str[i] != 0){
        if(!char_is_digit(str[i])){
            return 0;
        }
        i++;
    }
    return 1;
}

char* getProcessName(char *processDirFullName)
{
//    struct dirent *de;  // Pointer for directory entry
//    struct processData process;
//    char *processDirFullName;
//
//    DIR *dr = opendir("processDirFullName"); // opendir() returns a pointer of DIR type.
//
//    if (dr == NULL)  // opendir returns NULL if couldn't open directory
//    {
//        printf("Could not open current directory" );
//        return;
//    }
//
//    while ((de = readdir(dr)) != NULL)
//    {
//        if(str_is_digit(de->d_name) == 1)
//        {
//            processDirFullName = "/proc/" + de->d_name;
//            process.id = atoi(de->d_name);
//            process.name = getProcessName(processDirFullName);
//        }
//    }
//
//    closedir(dr);
return processDirFullName;
}

void getData(){
    struct dirent *de;  // Pointer for directory entry
    struct processData process;
    char *processDirFullName;

    DIR *dr = opendir("/proc"); // opendir() returns a pointer of DIR type.

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return;
    }

    while ((de = readdir(dr)) != NULL)
    {
        if(str_is_digit(de->d_name) == 1)
        {
            processDirFullName = strcat("/proc/", de->d_name);
            process.id = atoi(de->d_name);
            process.name = getProcessName(processDirFullName);
            printf("%i %s", process.id, process.name);
        }
    }

    closedir(dr);
}