#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
# include <ctype.h>
#include "../headers/dataManager.h"

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

/// Delete left spaces of a string
/// \param s The string to trim
/// \return The trimed string
char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

/// Delete right spaces of a string
/// \param s The string to trim
/// \return The trimed string
char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

/// Delete left and right spaces of a string
/// \param s The string to trim
/// \return The trimed string
char *trim(char *s)
{
    return rtrim(ltrim(s));
}

/// Copy a string
/// \param src The string to copy
/// \return A copy of the inputed string
char *my_strdup(char *src){
    int length = 0;

    while(src[length] != 0) {
        length++;
    }

    char *copy = (char*)malloc(sizeof(char) * length);

    length = 0;

    while(src[length] != 0){
        copy[length] = src[length];
        length++;
    }

    return copy;
}

/// Get the name of the process
/// \param processFileFullName Full path of the status file of the process
/// \return The name of the process
char* getProcessName(char *processFileFullName)
{
    char *processName;
    FILE *stream;

    if((stream = fopen(processFileFullName, "r")) != NULL) {
        char *line = malloc(sizeof(char) * 256);
        while (fgets(line, 256, stream) != NULL) { // for each line of the file
            if (strstr(line, "Name") != NULL) {
                processName = my_strdup(line);
                processName += 5;
                processName = trim(processName);
            }
        }
    }

    return processName;
}

/// Get the data of all the running processes
void getData(){
    struct processData process;
    char *baseDirName = "/proc", *fileToReadName = "status";

    struct dirent *dirEntries;  // Pointer for directory entry

    DIR *dr = opendir(baseDirName); // opendir() returns a pointer of DIR type.

    if (dr == NULL)  // opendir returns NULL if it couldn't open directory
    {
        printf("Could not open current directory" );
    }

    char *fileName;  // Name of the actual file
    int numLetter;  // Number of letters in the full path of the actual status file

    while ((dirEntries = readdir(dr)) != NULL)  // for each line
    {
        fileName = dirEntries->d_name;
        if(str_is_digit(fileName) == 1)
        {
            numLetter = strlen(baseDirName) + strlen(fileName) + strlen(fileToReadName) + 2;
            char processFileFullName[numLetter + 1];
            snprintf(processFileFullName, sizeof(processFileFullName), "%s/%s/%s", baseDirName, fileName, fileToReadName);  // Write the full name of the source's file in the processFileFullName string

            process.id = atoi(fileName);
            process.name = getProcessName(processFileFullName);
            printf("Process %i : %s\n", process.id, process.name);
        }
    }

    closedir(dr);
}