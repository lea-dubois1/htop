#ifndef HTOP_DATAMANAGER_H
#define HTOP_DATAMANAGER_H

int char_is_digit(char character);
int str_is_digit(char *str);
//char* getProcessName(char *processDirFullName);

struct processData
{
    int id;
    char *name;
};

void getData();

#endif //HTOP_DATAMANAGER_H
