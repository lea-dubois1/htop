#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "../headers/dataManager.h"

#define FILE_TO_READ_NAME "status"
#define STATUS_FILE_PATH_FORMAT "/proc/%s/status"

/// Check if a char is a number
/// \param character The char to check
/// \return 1 if the char is a number, 0 if it is not a number
int char_is_digit(char character){
    if(character < '0' || character > '9'){
        return 0;
    }
    return 1;
}

/// Check if a string only contains numbers
/// \param str The string to check
/// \return 1 if the string contains only numbers, 1 if it contains at least one non-numérical char
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

/// Delete left and right spaces of a string
/// \param src The string to trim
/// \return The trimed string
char *trim(char *src){
    int i = 0;
    int debut = 0;
    int firstTime = 1;

    while(src[i] != 0){
        if(isspace(src[i]) == 0){
            if(firstTime == 1){
                debut = i;
                firstTime = 0;
            }
        }
        i++;
    }

    int fin = 0;
    int firstTimeEnd = 1;

    while(i >= 0){
        if(isspace(src[i]) == 0){
            if(firstTimeEnd == 1){
                fin = i;
                firstTimeEnd = 0;
            }
        }
        i--;
    }

    int newStrLen = fin - debut + 2;

    char *result = (char*)malloc((sizeof(char) * newStrLen) + 1);

    int j = debut;

    while(j <= fin){
        result[j - debut] = src[j];
        j++;
    }
    result[j] = '\0';

    return result;
}

/// Copy a string
/// \param src The string to copy
/// \return A copy of the inputed string
char *my_strdup(char *src){
    int length = 0;

    while(src[length] != 0) {
        length++;
    }

    char *copy = (char*)malloc(sizeof(char) * length + 1);

    length = 0;

    while(src[length] != 0){
        copy[length] = src[length];
        length++;
    }
    copy[length] = '\0';

    return copy;
}

/// Get the name of the process
/// \param processFileFullName Full path of the status file of the process
/// \return The name of the process
char* getProcessName(char *processFileFullName)
{
    char *processName = NULL;
    FILE *stream;

    if((stream = fopen(processFileFullName, "r")) != NULL) {
        char *line = malloc(sizeof(char) * 256);
        while (fgets(line, 256, stream) != NULL) { // for each line of the file
            if (strstr(line, "Name") != NULL) {
                processName = my_strdup(line + 5);
                processName = trim(processName);
            }
        }
    }
    fclose(stream);
    return processName;
}

int getNumberProcesses(char *dirName)
{
    DIR *dr = opendir(dirName);
    if (!dr) return 0;
    struct dirent *dirEntries;
    int num = 0;
    while ((dirEntries = readdir(dr)) != NULL)
    {
        if(str_is_digit(dirEntries->d_name) == 1)
        {
            num++;
        }
    }
    closedir(dr);
    return num;
}

/// Get the data of all the running processes
Process* getData()
{
    DIR *dr = opendir(BASE_DIR_NAME); // opendir() returns a pointer of DIR type.
    Process *processes = (Process*) malloc(sizeof(Process) * (getNumberProcesses(BASE_DIR_NAME) + 1));

    if (dr == NULL)  // opendir returns NULL if it couldn't open directory
    {
        printf("Could not open current directory" );
    }

    struct dirent *dirEntries;  // Pointer for directory entry

    char *fileName;  // Name of the actual file
    int numLetter;  // Number of letters in the full path of the actual status filedirEntries = readdir(dr)

    int processNum = 0;
    while ((dirEntries = readdir(dr)) != NULL)  // for each line
    {
        fileName = dirEntries->d_name;
        if(str_is_digit(fileName) == 1)
        {
            numLetter = strlen(BASE_DIR_NAME) + strlen(fileName) + strlen(FILE_TO_READ_NAME) + 2;
            char processFileFullName[numLetter + 1];
            snprintf(processFileFullName, sizeof(processFileFullName), STATUS_FILE_PATH_FORMAT, fileName);  // Write the full name of the source's file in the processFileFullName string

            Process process;
            process.id = atoi(fileName);
            process.name = getProcessName(processFileFullName);
            processes[processNum] = process;
            processNum++;
        }
    }
    closedir(dr);
    return processes;
}