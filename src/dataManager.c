#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
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

char* getProcessName(char *processFileFullName)
{
    FILE *stream;

    char line[256];
    while(fgets(line, 256, *stream) != NULL){ // for each line of the file
        // si la ligne contient "Name"
        // récupérer le name
        // set process.name
    }

    return processFileFullName;
}

void getData(){
    struct dirent *de;  // Pointer for directory entry
    struct processData process;
    char *baseDirName = "/proc";
    char *fileToReadName = "status";

    DIR *dr = opendir(baseDirName); // opendir() returns a pointer of DIR type.

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return;
    }

    char *fileName;
    int numLetter;

    while ((de = readdir(dr)) != NULL)
    {
        fileName = de->d_name;
        if(str_is_digit(fileName) == 1)
        {
            numLetter = strlen(baseDirName) + strlen(fileName) + strlen(fileToReadName) + 2;
            char processFileFullName[numLetter + 1];
            snprintf(processFileFullName, sizeof(processFileFullName), "%s/%s/%s", baseDirName, fileName, fileToReadName);

            process.id = atoi(fileName);
            process.name = getProcessName(processFileFullName);
            printf("%s\n", processFileFullName);
        }
    }

    closedir(dr);
}